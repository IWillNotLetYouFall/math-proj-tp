#pragma once
#include "ParticleContact.h"

class ParticleContactResolver
{
protected:
	//Nombre max. d'itérations
	unsigned int iterations;

public:
	ParticleContactResolver(unsigned int iterations);
	//Prend en param un array de contacts,
	//Itération de chaque contact en fonction de leur separationVelocity
	//Arrêt lorsque tous les contacts sont résolus ou le max d'itérations est atteint.
	void ResolveContacts(vector<ParticleContact*> contactArray, unsigned int numContact, float duration);
};

