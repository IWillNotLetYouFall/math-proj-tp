#include "PhysicWorld.h"

PhysicWorld::PhysicWorld(int iterations)
{
	contactResolver = ParticleContactResolver(iterations);
}

void PhysicWorld::AddEntry(Particule* particleA, ParticleForceGenerator* force)
{
	registre.addEntry(particleA, force); //Main : Initialiser SpringParticle et fetch PA comme param constr
}

void PhysicWorld::AddContactGenerator(ParticleContactGenerator* contactGen)
{
	if (contactGen != NULL)
		contactsGenerators.push_back(contactGen);
}

void PhysicWorld::StartFrame()
{
	for (ParticleForceRegistry::ParticleForceEntry reg : registre.m_registry)
		reg.particle->clearForceAcc();
	registre.clearRegistry();
}

vector<ParticleContact*> PhysicWorld::GenerateContacts()
{
	vector<ParticleContact*> usedContacts;
	ParticleContact* used;
	for (ParticleContactGenerator* gen : contactsGenerators) {
		used = new ParticleContact();
		if (gen->addContact(used, 1) == 1) {
			usedContacts.push_back(used);
		}
	}
	return usedContacts;
}


void PhysicWorld::RunPhysics(float duration)
{
	contacts.clear();

	//TODO: Générer forces sur les particules
	registre.UpdateForce(duration);

	//Intégration sur chacune des particules
	for (ParticleForceRegistry::ParticleForceEntry reg : registre.m_registry)
		reg.particle->Integrate(duration);

	//Gestion des collisions
	//Génération des Contacts
	//contacts = GenerateContacts();

	//Résolution des contacts
	//contactResolver.ResolveContacts(contacts, contacts.size(), duration);
}
