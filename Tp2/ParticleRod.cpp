#include "ParticleRod.h"

unsigned int ParticleRod::addContact(ParticleContact* contact, unsigned int limit) const
{
    if (currentLength() != length) {
        contact->particle[0] = particle[0];
        contact->particle[1] = particle[1];
        Vector3D dir = particle[1]->position - particle[0]->position;
        Vector3D normalDir = dir.Normalize();
        float penetration = dir.GetNorm() - length;
        if (penetration < 0) {
            normalDir = normalDir.Inverse();
            penetration = -(penetration);
        }
        contact->contactNormal = normalDir;
        contact->penetration = penetration;

        return 1;
    }

    return 0;
}
