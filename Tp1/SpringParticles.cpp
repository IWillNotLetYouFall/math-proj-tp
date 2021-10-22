#include "SpringParticles.h"

//apply hooke's law from particles position
void SpringParticles::UpdateForce(Particule* particle, float duration)
{
	Vector3D dist = particle->position - m_other->position;
	Vector3D inc = dist.Normalize() * -m_k * (dist.GetNorm() - m_restLenght);
	particle->velocite += inc * duration;
}