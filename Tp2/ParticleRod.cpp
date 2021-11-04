#include "ParticleRod.h"

ParticleRod::ParticleRod(float length)
{
    this->length = length;
}

unsigned int ParticleRod::addContact(ParticleContact* contact, unsigned int limit) const
{
    if (currentLength() != length) {
        contact->particle[0] = particle[0];
        contact->particle[1] = particle[1];
        Vector3D dir = particle[0]->position - particle[1]->position;
        dir = dir.Normalize();
        float penetration = currentLength() - length;
        if (penetration < 0) {
            dir = dir * -1;
            penetration = -(penetration);
        }
        contact->contactNormal = dir;
        contact->penetration = penetration / 2;
        contact->restitution = 0;

        return 1;
    }

    return 0;
}
