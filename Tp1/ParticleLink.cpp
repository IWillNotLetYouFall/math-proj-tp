#include "ParticleLink.h"

float ParticleLink::currentLength() const
{
	Vector3D normalDir = particle[1]->position - particle[0]->position;
	return normalDir.GetNorm();
}
