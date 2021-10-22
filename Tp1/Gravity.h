#pragma once

#include "Forces.h"
#include "Vector3D.h"

class Gravity : public Forces
{
private:
	Vector3D m_gravity;

public:
	Gravity(Vector3D gravity) : m_gravity(gravity) {};

	// F = particle->GetMass()*m_gravity
	void UpdateForce(Particule* particle, float duration);
};