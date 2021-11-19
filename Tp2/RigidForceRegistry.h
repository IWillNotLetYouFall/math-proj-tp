#pragma once

#include "ForceGeneratorBody.h"
#include <vector>

class RigidForceRegistry
{
public:
	struct RigidForceEntry
	{
		RigidBody* rigid;
		ForceGeneratorBody* force;
	};

	using Registry = std::vector<RigidForceEntry>;
	Registry m_registry;
public:
	void addEntry(RigidBody* rigid, ForceGeneratorBody* force);
	void removeEntry(RigidBody* rigid, ForceGeneratorBody* force);
	void removeEntries(RigidBody* rigid);
	void clearRegistry();

	void UpdateForce(float duration);
};