#pragma once

#include "RigidBody.h"

/*
     * Forward declaration, see full declaration below for complete
     * documentation.
     */
class ContactResolver;

/**
 * A contact represents two bodies in contact. Resolving a
 * contact removes their interpenetration, and applies sufficient
 * impulse to keep them apart. Colliding bodies may also rebound.
 * Contacts can be used to represent positional joints, by making
 * the contact constraint keep the bodies in their correct
 * orientation.
 *
 * It can be a good idea to create a contact object even when the
 * contact isn't violated. Because resolving one contact can violate
 * another, contacts that are close to being violated should be
 * sent to the resolver; that way if one resolution moves the body,
 * the contact may be violated, and can be resolved. If the contact
 * is not violated, it will not be resolved, so you only loose a
 * small amount of execution time.
 *
 * The contact has no callable functions, it just holds the contact
 * details. To resolve a set of contacts, use the contact resolver
 * class.
 */
class OldContact
{
    // ... Other data as before ...

    /**
     * The contact resolver object needs access into the contacts to
     * set and effect the contact.
     */
    friend class ContactResolver;

public:
    /**
     * Holds the bodies that are involved in the contact. The
     * second of these can be NULL, for contacts with the scenery.
     */
    RigidBody* body[2];

    /**
     * Holds the lateral friction coefficient at the contact.
     */
    float friction;

    /**
     * Holds the normal restitution coefficient at the contact.
     */
    float restitution;

    /**
     * Holds the position of the contact in world coordinates.
     */
    Vector3D contactPoint;

    /**
     * Holds the direction of the contact in world coordinates.
     */
    Vector3D contactNormal;

    /**
     * Holds the depth of penetration at the contact point. If both
     * bodies are specified then the contact point should be midway
     * between the inter-penetrating points.
     */
    float penetration;

    /**
     * Sets the data that doesn't normally depend on the position
     * of the contact (i.e. the bodies, and their material properties).
     */
    void setBodyData(RigidBody* one, RigidBody* two,
        float friction, float restitution);

protected:

    /**
     * A transform matrix that converts co-ordinates in the contact's
     * frame of reference to world co-ordinates. The columns of this
     * matrix form an orthonormal set of vectors.
     */
    Matrix3 contactToWorld;

    /**
     * Holds the closing velocity at the point of contact. This is set
     * when the calculateInternals function is run.
     */
    Vector3D contactVelocity;

    /**
     * Holds the required change in velocity for this contact to be
     * resolved.
     */
    float desiredDeltaVelocity;

    /**
     * Holds the world space position of the contact point relative to
     * centre of each body. This is set when the calculateInternals
     * function is run.
     */
    Vector3D relativeContactPosition[2];

protected:
    /**
     * Calculates internal data from state data. This is called before
     * the resolution algorithm tries to do any resolution. It should
     * never need to be called manually.
     */
    void calculateInternals(float duration);

    /**
     * Reverses the contact. This involves swapping the two rigid bodies
     * and reversing the contact normal. The internal values should then
     * be recalculated using calculateInternals (this is not done
     * automatically).
     */
    void swapBodies();

    /**
     * Updates the awake state of rigid bodies that are taking
     * place in the given contact. A body will be made awake if it
     * is in contact with a body that is awake.
     */
    void matchAwakeState();

    /**
     * Calculates and sets the internal value for the desired delta
     * velocity.
     */
    void calculateDesiredDeltaVelocity(float duration);

    /**
     * Calculates and returns the velocity of the contact
     * point on the given body.
     */
    Vector3D calculateLocalVelocity(unsigned bodyIndex, float duration);

    /**
     * Calculates an orthonormal basis for the contact point, based on
     * the primary friction direction (for anisotropic friction) or
     * a random orientation (for isotropic friction).
     */
    void calculateContactBasis();

    /**
     * Applies an impulse to the given body, returning the
     * change in velocities.
     */
    void applyImpulse(const Vector3D& impulse, RigidBody* body,
        Vector3D* velocityChange, Vector3D* rotationChange);

    /**
     * Performs an inertia-weighted impulse based resolution of this
     * contact alone.
     */
    void applyVelocityChange(Vector3D velocityChange[2],
        Vector3D rotationChange[2]);

    /**
     * Performs an inertia weighted penetration resolution of this
     * contact alone.
     */
    void applyPositionChange(Vector3D linearChange[2],
        Vector3D angularChange[2],
        float penetration);

    /**
     * Calculates the impulse needed to resolve this contact,
     * given that the contact has no friction. A pair of inertia
     * tensors - one for each contact object - is specified to
     * save calculation time: the calling function has access to
     * these anyway.
     */
    Vector3D calculateFrictionlessImpulse(Matrix3* inverseInertiaTensor);

    /**
     * Calculates the impulse needed to resolve this contact,
     * given that the contact has a non-zero coefficient of
     * friction. A pair of inertia tensors - one for each contact
     * object - is specified to save calculation time: the calling
     * function has access to these anyway.
     */
    Vector3D calculateFrictionImpulse(Matrix3* inverseInertiaTensor);
};

/**
 * The contact resolution routine. One resolver instance
 * can be shared for the whole simulation, as long as you need
 * roughly the same parameters each time (which is normal).
 *
 * @section algorithm Resolution Algorithm
 *
 * The resolver uses an iterative satisfaction algorithm; it loops
 * through each contact and tries to resolve it. Each contact is
 * resolved locally, which may in turn put other contacts in a worse
 * position. The algorithm then revisits other contacts and repeats
 * the process up to a specified iteration limit. It can be proved
 * that given enough iterations, the simulation will get to the
 * correct result. As with all approaches, numerical stability can
 * cause problems that make a correct resolution impossible.
 *
 * @subsection strengths Strengths
 *
 * This algorithm is very fast, much faster than other physics
 * approaches. Even using many more iterations than there are
 * contacts, it will be faster than global approaches.
 *
 * Many global algorithms are unstable under high friction, this
 * approach is very robust indeed for high friction and low
 * restitution values.
 *
 * The algorithm produces visually believable behaviour. Tradeoffs
 * have been made to err on the side of visual floatism rather than
 * computational expense or numerical accuracy.
 *
 * @subsection weaknesses Weaknesses
 *
 * The algorithm does not cope well with situations with many
 * inter-related contacts: stacked boxes, for example. In this
 * case the simulation may appear to jiggle slightly, which often
 * dislodges a box from the stack, allowing it to collapse.
 *
 * Another issue with the resolution mechanism is that resolving
 * one contact may make another contact move sideways against
 * friction, because each contact is handled independently, this
 * friction is not taken into account. If one object is pushing
 * against another, the pushed object may move across its support
 * without friction, even though friction is set between those bodies.
 *
 * In general this resolver is not suitable for stacks of bodies,
 * but is perfect for handling impact, explosive, and flat resting
 * situations.
 */
class ContactResolver
{
protected:
    /**
     * Holds the number of iterations to perform when resolving
     * velocity.
     */
    unsigned velocityIterations;

    /**
     * Holds the number of iterations to perform when resolving
     * position.
     */
    unsigned positionIterations;

    /**
     * To avoid instability velocities smaller
     * than this value are considered to be zero. Too small and the
     * simulation may be unstable, too large and the bodies may
     * interpenetrate visually. A good starting point is the default
     * of 0.01.
     */
    float velocityEpsilon;

    /**
     * To avoid instability penetrations
     * smaller than this value are considered to be not interpenetrating.
     * Too small and the simulation may be unstable, too large and the
     * bodies may interpenetrate visually. A good starting point is
     * the default of0.01.
     */
    float positionEpsilon;

public:
    /**
     * Stores the number of velocity iterations used in the
     * last call to resolve contacts.
     */
    unsigned velocityIterationsUsed;

    /**
     * Stores the number of position iterations used in the
     * last call to resolve contacts.
     */
    unsigned positionIterationsUsed;

private:
    /**
     * Keeps track of whether the internal settings are valid.
     */
    bool validSettings;

public:
    /**
     * Creates a new contact resolver with the given number of iterations
     * per resolution call, and optional epsilon values.
     */
    ContactResolver(unsigned iterations,
        float velocityEpsilon = (float)0.01,
        float positionEpsilon = (float)0.01);

    /**
     * Creates a new contact resolver with the given number of iterations
     * for each kind of resolution, and optional epsilon values.
     */
    ContactResolver(unsigned velocityIterations,
        unsigned positionIterations,
        float velocityEpsilon = (float)0.01,
        float positionEpsilon = (float)0.01);

    /**
     * Returns true if the resolver has valid settings and is ready to go.
     */
    bool isValid()
    {
        return (velocityIterations > 0) &&
            (positionIterations > 0) &&
            (positionEpsilon >= 0.0f);
    }

    /**
     * Sets the number of iterations for each resolution stage.
     */
    void setIterations(unsigned velocityIterations,
        unsigned positionIterations);

    /**
     * Sets the number of iterations for both resolution stages.
     */
    void setIterations(unsigned iterations);

    /**
     * Sets the tolerance value for both velocity and position.
     */
    void setEpsilon(float velocityEpsilon,
        float positionEpsilon);

    /**
     * Resolves a set of contacts for both penetration and velocity.
     *
     * Contacts that cannot interact with
     * each other should be passed to separate calls to resolveContacts,
     * as the resolution algorithm takes much longer for lots of
     * contacts than it does for the same number of contacts in small
     * sets.
     *
     * @param contactArray Pointer to an array of contact objects.
     *
     * @param numContacts The number of contacts in the array to resolve.
     *
     * @param numIterations The number of iterations through the
     * resolution algorithm. This should be at least the number of
     * contacts (otherwise some constraints will not be resolved -
     * although sometimes this is not noticable). If the iterations are
     * not needed they will not be used, so adding more iterations may
     * not make any difference. In some cases you would need millions
     * of iterations. Think about the number of iterations as a bound:
     * if you specify a large number, sometimes the algorithm WILL use
     * it, and you may drop lots of frames.
     *
     * @param duration The duration of the previous integration step.
     * This is used to compensate for forces applied.
     */
    void resolveContacts(OldContact* contactArray,
        unsigned numContacts,
        float duration);

protected:
    /**
     * Sets up contacts ready for processing. This makes sure their
     * internal data is configured correctly and the correct set of bodies
     * is made alive.
     */
    void prepareContacts(OldContact* contactArray, unsigned numContacts,
        float duration);

    /**
     * Resolves the velocity issues with the given array of constraints,
     * using the given number of iterations.
     */
    void adjustVelocities(OldContact* contactArray,
        unsigned numContacts,
        float duration);

    /**
     * Resolves the positional issues with the given array of constraints,
     * using the given number of iterations.
     */
    void adjustPositions(OldContact* contacts,
        unsigned numContacts,
        float duration);
};

/**
 * This is the basic polymorphic interface for contact generators
 * applying to rigid bodies.
 */
class ContactGenerator
{
public:
    /**
     * Fills the given contact structure with the generated
     * contact. The contact pointer should point to the first
     * available contact in a contact array, where limit is the
     * maximum number of contacts in the array that can be written
     * to. The method returns the number of contacts that have
     * been written.
     */
    virtual unsigned addContact(OldContact* contact, unsigned limit) const = 0;
};