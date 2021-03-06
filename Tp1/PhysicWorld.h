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
	vector<Particule> particules;
	vector<ParticleForceGenerator> forcesGen;
	vector<ParticleContactGenerator> contactsGen;
	vector<ParticleContactResolver> contactsResolver;

public:
	PhysicWorld();
	void RunPhysics(float duration);
};

