#include "PhysicWorld.h"

void PhysicWorld::RunPhysics(float duration)
{
	//TODO: Générer forces sur les particules


	//TODO: Effectuer la tâche d’intégration sur chacune des particules


	//TODO: Détecter et faire la gestion des collisions
	//vector<>
	//Génération des Contacts


	//Résolution des contacts

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
