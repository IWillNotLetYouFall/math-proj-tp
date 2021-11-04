#include "ParticleLink.h"

float ParticleLink::currentLength() const
{
	Vector3D normalDir = particle[0]->position - particle[1]->position;
	return normalDir.GetNorm();
}
