#pragma once
#include "Vector3D.h"
#include <cmath>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include "ForceGenerator.h"
#include "ContactGenerator.h"
#include "ContactResolver.h"
#include "Particule.h"

using namespace sf;
using namespace std;

class PhysicWorld
{
public:
	vector<Particule> particules;
	vector<ForceGenerator> forcesGen;
	vector<ContactGenerator> contactsGen;
	vector<ContactResolver> contactsResolver;

public:
	PhysicWorld();
	void RunPhysics(float duration);
};

