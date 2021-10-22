#include "ForcesRegistry.h"

void ForcesRegistry::addEntry(Particule* particle, Forces* force)
{
	ParticleForceEntry newEntry;
	newEntry.particle = particle;
	newEntry.force = force;
	m_registry.push_back(newEntry);
}

void ForcesRegistry::UpdateForce(float duration)
{
	for (ParticleForceEntry entry : m_registry)
	{
		entry.force->UpdateForce(entry.particle, duration);
	}

	m_registry.clear();
}