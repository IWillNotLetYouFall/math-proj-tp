#pragma once

#include "Forces.h"
#include <vector>

class ForcesRegistry
{
private:
	struct ParticleForceEntry
	{
		Particule* particle;
		Forces* force;
	};

	using Registry = std::vector<ParticleForceEntry>;
	Registry m_registry;
public:
	void addEntry(Particule* particle, Forces* force);

	void UpdateForce(float duration);
};