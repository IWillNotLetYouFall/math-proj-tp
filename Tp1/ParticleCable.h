#pragma once
#include "ParticleLink.h"

class ParticleCable : ParticleLink
{
	float maxLength;

	float restitution;

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};
