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
#include "ParticleCable.h"
#include <algorithm>
#include "RigidBody.h"

using namespace sf;
using namespace std;

class PhysicWorld
{
private:
	vector<RigidBody*> integratedParts;
public:
	ParticleForceRegistry registre;
	vector<ParticleContact*> contacts;
	vector<RigidBody*> rigidReg;

	vector<ParticleContactGenerator*> contactsGenerators;
	ParticleContactResolver contactResolver;

public:
	PhysicWorld(int iterations);

	void AddEntry(RigidBody* rigid, ParticleForceGenerator* force);
	void RemoveEntries(RigidBody* rigid);
	void AddRigidBody(RigidBody* rigid);
	void RemoveRigidBody(RigidBody* rigid);
	void AddContactGenerator(ParticleContactGenerator* contactGen);

	//void RemoveEntry(Particule* particleA);
	void StartFrame();
	vector<ParticleContact*> GenerateContacts();
	void RunPhysics(float duration);
};

