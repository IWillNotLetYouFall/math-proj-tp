#include "ParticleGravity.h"

// F = particle->GetMass()*m_gravity
void ParticleGravity::UpdateForce(Particule* particle, float duration)
{
	if (particle->InverseMasse() <= 0) return;

	particle->addForce(m_gravity * particle->GetMasse());
}