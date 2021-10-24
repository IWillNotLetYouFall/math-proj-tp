#pragma once

#include "ParticleForceGenerator.h"

//Spring between two elements only when distance is longer than restLenght

class SpringBungee : public ParticleForceGenerator
{
	//other anchor
	Particule* m_other;

	//Spring constant
	float m_k;

	float m_restLenght;

public:
	SpringBungee(Particule* particle, float k, float restLenght) : m_other(particle), m_k(k), m_restLenght(restLenght) {};

	//apply hooke's law from particles position
	void UpdateForce(Particule* particle, float duration);
};