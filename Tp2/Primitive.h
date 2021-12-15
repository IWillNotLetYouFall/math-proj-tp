#pragma once
#include "RigidBody.h"

class Primitive
{

public:
	RigidBody* body;
	Matrix4 offset;
};