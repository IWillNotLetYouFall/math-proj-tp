#include "Friction.h"

// apply simplified drag based on particle's velocity
void Friction::UpdateForce(Particule* particle, float duration)
{
	Vector3D vel = particle->velocite;
	float p = vel.GetNorm();

	Vector3D inc = vel.Normalize() * -1 * (m_k1 * p + m_k2 * (p * p));
	particle->addForce(inc);
}