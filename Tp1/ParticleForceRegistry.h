#pragma once

#include "ParticleForceGenerator.h"
#include <vector>

class ParticleForceRegistry
{
private:
	struct ParticleForceEntry
	{
		Particule* particle;
		ParticleForceGenerator* force;
	};

	using Registry = std::vector<ParticleForceEntry>;
	Registry m_registry;
public:
	void addEntry(Particule* particle, ParticleForceGenerator* force);

	void UpdateForce(float duration);
};