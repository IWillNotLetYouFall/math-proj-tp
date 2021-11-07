#include "SpringParticles.h"

//apply hooke's law from particles position
void SpringParticles::UpdateForce(Particule* particle, float duration)
{
	Vector3D dist = particle->position - m_other->position;
	if (dist.GetNorm() == 0) return;

	Vector3D inc = dist.Normalize() * -m_k * abs(dist.GetNorm() - m_restLenght);
	particle->addForce(inc);
}