#pragma once
#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator
{
public:
	Particule* particle[2];

	void setParticle1(Particule* p) { particle[0] = p; };
	void setParticle2(Particule* p) { particle[1] = p; };

	float currentLength() const;

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;
};
