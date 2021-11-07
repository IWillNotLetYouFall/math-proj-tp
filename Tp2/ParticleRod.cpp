#include "ParticleRod.h"

ParticleRod::ParticleRod(float length)
{
    this->length = length;
}

unsigned int ParticleRod::addContact(ParticleContact* contact, unsigned int limit) const
{
    float currLen = currentLength();
    if (currLen != length) {
        contact->particle[0] = particle[0];
        contact->particle[1] = particle[1];
        Vector3D dir = particle[1]->position - particle[0]->position;
        dir = dir.Normalize();
        if (currLen > length) {
            contact->contactNormal = dir;
            contact->penetration = currLen - length;
        }
        else {
            contact->contactNormal = dir * -1;
            contact->penetration = length - currLen;
        }
        contact->restitution = 0;

        return 1;
    }

    return 0;
}
