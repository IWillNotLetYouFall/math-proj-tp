#pragma once

#include "ParticleForceGenerator.h"
#include "Vector3D.h"

class ParticleGravity : public ParticleForceGenerator
{
private:
	Vector3D m_gravity;

public:
	ParticleGravity(Vector3D gravity) : m_gravity(gravity) {};

	// F = particle->GetMass()*m_gravity
	void UpdateForce(Particule* particle, float duration);
};