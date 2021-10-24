#pragma once
#include "Particule.h"

class ParticleForceGenerator
{
public:
	// interface function
	virtual void UpdateForce(Particule* particle, float duration) = 0;
	void GenerateGenerators();
	void GenerateGenerator();
};