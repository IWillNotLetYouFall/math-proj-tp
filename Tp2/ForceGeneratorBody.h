#pragma once
#include "RigidBody.h"

class ForceGeneratorBody
{
public:
	//Apply force to the rigidBody
	virtual void UpdateForce(RigidBody* rigidbody) = 0;
};