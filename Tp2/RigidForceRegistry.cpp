#include "RigidForceRegistry.h"
#include <iostream>

void RigidForceRegistry::addEntry(RigidBody* rigid, ForceGeneratorBody* force)
{
	RigidForceEntry newEntry;
	newEntry.rigid = rigid;
	newEntry.force = force;
	m_registry.push_back(newEntry);
}

void RigidForceRegistry::removeEntry(RigidBody* rigid, ForceGeneratorBody* force)
{
	int i = 0;
	for (RigidForceEntry entry : m_registry)
	{
		if (entry.force == force)
		{
			if (entry.rigid == rigid)
			{
				m_registry.erase(m_registry.begin() + i);
				break;
			}
		}
		i++;
	}
}

void RigidForceRegistry::removeEntries(RigidBody* rigid)
{
	int i = 0;
	for (RigidForceEntry entry : m_registry)
	{
		if (entry.rigid == rigid)
			m_registry.erase(m_registry.begin() + i);
		else
			i++;
	}
}

void RigidForceRegistry::clearRegistry()
{
	m_registry.clear();
}

void RigidForceRegistry::UpdateForce(float duration)
{
	for (RigidForceEntry entry : m_registry)
	{
		entry.force->UpdateForce(entry.rigid);
	}

	//m_registry.clear();
}