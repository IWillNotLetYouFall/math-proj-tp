#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Vector3D.h"
#include <math.h>
#include <vector>
#include <cstdlib>
#include "PhysicWorld.h"
#include "RigidBody.h"
#include "Primitive.h"

class OctTree
{
public:
	Vector3D posiiton;
	Vector3D size;
	vector<Primitive> m_objects;

public:
	OctTree();
};

