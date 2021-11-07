#include "SpringFixed.h"

//apply hooke's law from particles position
void SpringFixed::UpdateForce(Particule* particle, float duration)
{
	Vector3D dist = particle->position - m_anchor;
	if (dist.GetNorm() == 0) return;

	Vector3D inc = dist.Normalize() * -m_k * abs(dist.GetNorm() - m_restLenght);
	particle->addForce(inc);
}