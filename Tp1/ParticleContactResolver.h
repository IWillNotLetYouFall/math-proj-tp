#pragma once
#include "ParticleContact.h"

class ParticleContactResolver
{
protected:
	//Nombre max. d'it�rations
	unsigned int iteration;

public:
	//Prend en param un array de contacts,
	//It�ration de chaque contact en fonction de leur separationVelocity
	//Arr�t lorsque tous les contacts sont r�solus ou le max d'it�rations est atteint.
	void ResolveContacts(ParticleContact* contactArray, unsigned int numContact, float duration);
};

