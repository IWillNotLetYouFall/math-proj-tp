#pragma once

#include "Primitive.h"
#include "Sphere.h"

class Box : public Primitive
{

public:
	Vector3D halfsize;
	Sphere BoundingSphere;
};