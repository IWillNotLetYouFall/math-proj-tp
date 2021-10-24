#pragma once
#include "Vector3D.h"
#include <cmath>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include "ParticleForceGenerator.h"
#include "ParticleContactGenerator.h"
#include "ParticleContactResolver.h"
#include "Particule.h"

using namespace sf;
using namespace std;

class PhysicWorld
{
public:
	vector<Particule*> particules;
	vector<ParticleForceGenerator*> forcesGen;
	vector<ParticleContactGenerator*> contactsGen;
	ParticleContactResolver* contactResolver;

public:
	PhysicWorld();
	void RunPhysics(float duration);
	void AddParticle(Particule* particle);
	void RemoveParticle(Particule* particle);
};

