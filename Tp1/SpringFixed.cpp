#include "SpringFixed.h"

//apply hooke's law from particles position
void SpringFixed::UpdateForce(Particule* particle, float duration)
{
	Vector3D dist = particle->position - m_anchor;
	Vector3D inc = dist.Normalize() * -m_k * (dist.GetNorm() - m_restLenght);
	particle->velocite += inc * duration;
}