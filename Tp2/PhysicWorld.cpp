#include "PhysicWorld.h"

PhysicWorld::PhysicWorld(int iterations)
{
	contactResolver = ParticleContactResolver(iterations);
}

void PhysicWorld::AddEntry(Particule* particleA, ParticleForceGenerator* force, ParticleCable* contactGen)
{
	registre.addEntry(particleA, force); //Main : Initialiser SpringParticle et fetch PA comme param constr

	if (contactGen != NULL)
		contactsGenerators.push_back(contactGen);
}

void PhysicWorld::StartFrame()
{
	for (ParticleForceRegistry::ParticleForceEntry reg : registre.m_registry)
		reg.particle->clearForceAcc();
}

vector<ParticleContact*> PhysicWorld::GenerateContacts()
{
	vector<ParticleContact*> usedContacts;
	ParticleContact* used;
	for (ParticleCable* gen : contactsGenerators) {
		used = new ParticleContact();
		if (gen->addContact(used, 1) == 1) {
			usedContacts.push_back(used);
		}
	}
	return usedContacts;
}


void PhysicWorld::RunPhysics(float duration)
{
	//contacts.clear();

	//TODO: G�n�rer forces sur les particules
	registre.UpdateForce(duration);

	//Int�gration sur chacune des particules
	for (ParticleForceRegistry::ParticleForceEntry reg : registre.m_registry)
		reg.particle->Integrate(duration);

	//Gestion des collisions
	//vector<ParticleContact*> usedContacts;
	//G�n�ration des Contacts
	//contacts = GenerateContacts();

	//R�solution des contacts
	//contactResolver.ResolveContacts(contacts, contacts.size(), duration);
}