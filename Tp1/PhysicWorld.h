#pragma once
#include "Vector3D.h"
#include <cmath>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "ParticleForceGenerator.h"
#include "ParticleContactGenerator.h"
#include "ParticleContactResolver.h"
#include "Particule.h"
#include "ParticleForceRegistry.h"

using namespace sf;
using namespace std;

class PhysicWorld
{
public:
	ParticleForceRegistry registre;
	vector<ParticleContact*> contacts;

	//vector<ParticleContactGenerator*> contactsGen;
	ParticleContactResolver* contactResolver;

public:
	PhysicWorld();
	void StartFrame();
	void GenerateContacts(int limit);
	void RunPhysics(float duration);
};

