#include "SpringBungee.h"

//apply hooke's law from particles position
void SpringBungee::UpdateForce(Particule* particle, float duration)
{
	float distf = sqrtf(powf(particle->position.x - m_other->position.x, 2) + 
						powf(particle->position.y - m_other->position.y, 2) +
						powf(particle->position.z - m_other->position.z, 2));

	if (distf > m_restLenght)
	{
		Vector3D dist = particle->position - m_other->position;
		Vector3D inc = dist.Normalize() * -m_k * (dist.GetNorm() - m_restLenght);
		particle->velocite += inc;
	}
}