#pragma once
#include "Vector3D.h"
#include <cmath>
#include <iostream>
#include <string>
#include "Rigidbody.h"

class Contact
{
public:
	//Particle[0] is A, [1] is B
	RigidBody* rigid[2];

	//Distance penetration contact
	float penetration;

	//direction normalisée du contact
	Vector3D contactNormal;

	//Point de contact
	Vector3D contactPoint;
};

