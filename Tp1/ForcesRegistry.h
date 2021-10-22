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

	using Registry = std::vector<Forces>;
	Registry m_registry;
public:
	//...add registry accessors

	void UpdateForce(float duration);
};