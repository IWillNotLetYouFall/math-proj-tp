#pragma once
#include "ParticleContactGenerator.h"

using namespace std;

class CircleParticleContactGenerator : public ParticleContactGenerator
{
	float radius;

	vector<Particule> particles;

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

