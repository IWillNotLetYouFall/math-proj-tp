#include "ParticleCable.h"

unsigned int ParticleCable::addContact(ParticleContact* contact, unsigned int limit) const
{
    if (currentLength() > maxLength) {
        contact->particle[0] = particle[0];
        contact->particle[1] = particle[1];

        Vector3D normalDir = particle[1]->position - particle[0]->position;
        contact->contactNormal = normalDir;
        contact->restitution = restitution;
        return 1;
    }

    return 0;
}
