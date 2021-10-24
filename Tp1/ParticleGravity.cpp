#include "ParticleGravity.h"

// F = particle->GetMass()*m_gravity
void ParticleGravity::UpdateForce(Particule* particle, float duration)
{
	Vector3D inc = m_gravity * particle->GetMasse();
	particle->velocite += inc * duration;
}