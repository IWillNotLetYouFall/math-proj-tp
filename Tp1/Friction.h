#pragma once

#include "Forces.h"

class Friction : public Forces
{
private:
	// drag coeffiecents
	float m_k1;
	float m_k2;

public:
	Friction(float k1, float k2) : m_k1(k1), m_k2(k2) {};

	// apply simplified drag based on particle's velocity
	void UpdateForce(Particule* particle, float duration);
};
