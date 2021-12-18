#pragma once

#include "Vector3D.h"
#include <cmath>
#include <iostream>
#include <string>
#include "Rigidbody.h"

class Primitive
{
public:
	Matrix4 offset;
	RigidBody* body;

public:
	const Matrix4& GetTransform() { return body->GetTransformMatrix(); };
};