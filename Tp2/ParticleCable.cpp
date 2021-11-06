#include "ParticleCable.h"

ParticleCable::ParticleCable(float maxLength, float restitution)
{
    this->maxLength = maxLength;
    this->restitution = restitution;
}

unsigned int ParticleCable::addContact(ParticleContact* contact, unsigned int limit) const
{
    float currLength = currentLength();
    if (currLength >= maxLength) {
        contact->particle[0] = particle[0];
        contact->particle[1] = particle[1];

        Vector3D normalDir = (particle[1]->position - particle[0]->position).Normalize();
        contact->contactNormal = normalDir;
        contact->restitution = restitution;
        contact->penetration = currLength - maxLength;
        return 1;
    }

    return 0;
}
