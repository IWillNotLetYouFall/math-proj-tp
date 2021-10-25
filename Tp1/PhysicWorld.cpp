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
	//TODO: G�n�rer forces sur les particules
	registre.UpdateForce(duration);

	//Int�gration sur chacune des particules
	for (ParticleForceRegistry::ParticleForceEntry reg : registre.m_registry)
		reg.particle->Integrate(duration);

	//Gestion des collisions
	vector<ParticleContact*> contacts;
	//G�n�ration des Contacts
	GenerateContacts(10);

	//R�solution des contacts
	contactResolver->ResolveContacts(contacts, contacts.size(), duration);
}
