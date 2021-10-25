#include "PhysicWorld.h"

void PhysicWorld::StartFrame()
{
	//for (ParticleForceRegistry::ParticleForceEntry reg : registre.m_registry)
		//reg.particle->clearAccumulator();
}

void PhysicWorld::GenerateContacts(int limit)
{

}

void PhysicWorld::RunPhysics(float duration)
{
	//TODO: Générer forces sur les particules
	registre.UpdateForce(duration);

	//Intégration sur chacune des particules
	for (ParticleForceRegistry::ParticleForceEntry reg : registre.m_registry)
		reg.particle->Integrate(duration);

	//Gestion des collisions
	vector<ParticleContact*> contacts;
	//Génération des Contacts
	GenerateContacts(10);

	//Résolution des contacts
	contactResolver->ResolveContacts(contacts, contacts.size(), duration);
}
