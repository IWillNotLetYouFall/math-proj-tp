#pragma once
#include "ParticleLink.h"

class ParticleCable : ParticleLink
{
	float maxLength;

	float restitution;

public:
	ParticleCable(float maxLength, float restitution);

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;

	void setParticle1(Particule* p) { particle[0] = p; };
	void setParticle2(Particule* p) { particle[1] = p; };
};
