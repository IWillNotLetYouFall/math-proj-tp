#include "SpringBungee.h"

//apply hooke's law from particles position
void SpringBungee::UpdateForce(Particule* particle, float duration)
{
	Vector3D dist = particle->position - m_other->position;
	Vector3D dist2 = particle->position+particle->velocite - m_other->position;

	if (dist.GetNorm() > m_restLenght)
	{
		Vector3D inc = dist.Normalize() * -m_k * abs(dist.GetNorm() - m_restLenght);

		if (dist2.GetNorm() <= m_restLenght) inc /= 2;
		particle->addForce(inc);
	}
}