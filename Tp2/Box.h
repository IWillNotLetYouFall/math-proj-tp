#pragma once

#include "Primitive.h"
#include "Sphere.h"

class Box : public Primitive
{
public:
	Vector3D halfsize;
	//Sphere BoundingSphere;

public:
	float TransformToAxis(const Vector3D &axis);
	Vector3D GetAxis(int index) { 
		//Matrix4 mat = body->GetTransformMatrix();
		Matrix4 transform = GetTransform(); // * offset 
		return transform.GetAxisVector(index);
	}
};