#include "PhysicWorld.h"

void PhysicWorld::RunPhysics(float duration)
{
	//TODO: G�n�rer forces sur les particules


	//TODO: Effectuer la t�che d�int�gration sur chacune des particules


	//TODO: D�tecter et faire la gestion des collisions
	//vector<>
	//G�n�ration des Contacts


	//R�solution des contacts

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
