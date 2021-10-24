#pragma once
#include "ParticleLink.h"

class ParticleRod : ParticleLink
{
	float length;

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

