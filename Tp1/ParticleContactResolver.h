#pragma once
#include "ParticleContact.h"

class ParticleContactResolver
{
protected:
	//Nombre max. d'itérations
	unsigned int iteration;

public:
	//Prend en param un array de contacts,
	//Itération de chaque contact en fonction de leur separationVelocity
	//Arrêt lorsque tous les contacts sont résolus ou le max d'itérations est atteint.
	void ResolveContacts(ParticleContact* contactArray, unsigned int numContact, float duration);
};

