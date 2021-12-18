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
#include "RigidForceRegistry.h"

using namespace sf;
using namespace std;

class PhysicWorld
{
private:
	vector<RigidBody*> integratedParts;
public:
	//ParticleForceRegistry registre;
	RigidForceRegistry registre;

	vector<ParticleContact*> contacts;
	vector<RigidBody*> rigidReg;

	vector<ParticleContactGenerator*> contactsGenerators;
	ParticleContactResolver contactResolver;

	Vector3D coordinates;
	float halfsize;

public:
	PhysicWorld(int iterations);

	void AddEntry(RigidBody* rigid, ForceGeneratorBody* force);
	void RemoveEntries(RigidBody* rigid);
	void AddRigidBody(RigidBody* rigid);
	void RemoveRigidBody(RigidBody* rigid);
	void AddContactGenerator(ParticleContactGenerator* contactGen);

	//void RemoveEntry(Particule* particleA);
	void StartFrame();
	vector<ParticleContact*> GenerateContacts();
	void RunPhysics(float duration);

	void addCoordinates(float x, float y, float z)
	{
		halfsize = x / 2;
		coordinates = Vector3D(x, y, z);
	}
};

