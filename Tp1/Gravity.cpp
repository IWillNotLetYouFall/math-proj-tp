#include "Gravity.h"

// F = particle->GetMass()*m_gravity
void Gravity::UpdateForce(Particule* particle, float duration)
{
	Vector3D inc = m_gravity * particle->GetMasse();
	particle->velocite += inc;
}