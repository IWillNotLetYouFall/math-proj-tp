#include "PhysicWorld.h"

void PhysicWorld::RunPhysics(float duration)
{
	//TODO: Générer forces sur les particules


	//Intégration sur chacune des particules
	for (Particule* particule : particules)
		particule->Integrate(duration);

	//Gestion des collisions
	vector<ParticleContact*> contacts;
	//Génération des Contacts


	//Résolution des contacts
	contactResolver->ResolveContacts(contacts, contacts.size(), duration);
}

void PhysicWorld::AddParticle(Particule* particle)
{
	particules.push_back(particle);
}

void PhysicWorld::RemoveParticle(Particule* particle)
{
	for (int i = 0; i < particules.size(); i++)
	{
		if (particules[i] == particle) {
			particules.erase(particules.begin() + i);
			return;
		}
	}
}
