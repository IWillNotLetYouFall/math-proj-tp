#pragma once
#include "ParticleLink.h"

class ParticleCable : public ParticleLink
{
	float maxLength;

	float restitution;

public:
	ParticleCable(float maxLength, float restitution);

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};
