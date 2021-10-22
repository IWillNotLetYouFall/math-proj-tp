#include "ParticleForceRegistry.h"

void ParticleForceRegistry::addEntry(Particule* particle, ParticleForceGenerator* force)
{
	ParticleForceEntry newEntry;
	newEntry.particle = particle;
	newEntry.force = force;
	//m_registry.push_back(newEntry);
}

void ParticleForceRegistry::UpdateForce(float duration)
{
	//for (ParticleForceEntry entry : m_registry)
	//{
	//	entry.force->UpdateForce(entry.particle, duration);
	//}

	m_registry.clear();
}