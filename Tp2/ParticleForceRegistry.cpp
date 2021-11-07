#include "ParticleForceRegistry.h"
#include <iostream>

void ParticleForceRegistry::addEntry(Particule* particle, ParticleForceGenerator* force)
{
	ParticleForceEntry newEntry;
	newEntry.particle = particle;
	newEntry.force = force;
	m_registry.push_back(newEntry);
}

void ParticleForceRegistry::removeEntry(Particule* particle, ParticleForceGenerator* force)
{
	int i = 0;
	for (ParticleForceEntry entry : m_registry)
	{
		if (entry.force == force)
		{
			if (entry.particle == particle)
			{
				m_registry.erase(m_registry.begin() + i);
				break;
			}
		}
		i++;
	}
}

void ParticleForceRegistry::removeEntries(Particule* particle)
{
	int i = 0;
	for (ParticleForceEntry entry : m_registry)
	{
		if (entry.particle == particle)
			m_registry.erase(m_registry.begin() + i);
		else
			i++;
	}
}

void ParticleForceRegistry::clearRegistry()
{
	m_registry.clear();
}

void ParticleForceRegistry::UpdateForce(float duration)
{
	for (ParticleForceEntry entry : m_registry)
	{
		entry.force->UpdateForce(entry.particle, duration);
	}

	//m_registry.clear();
}