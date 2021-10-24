#pragma once
#include "ParticleContact.h"

class ParticleContactGenerator
{
public:
	// Prend un array de contact et le nombre de contacts restants � g�n�rer
	virtual unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;

};

