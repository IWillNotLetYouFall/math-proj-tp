#pragma once
#include "Vector3D.h"
#include "Quaternion.h"
class Matrix4
{
private:
	//values of the matrix3
	float values[12];

public:
	//combination of linear transformation
	Matrix4 operator*(const Matrix4& other) const;

	//Transform of a vector
	Vector3D operator* (const Vector3D& vector) const;

	//Get the Inverse matrix
	Matrix4 Inverse();

	//Set the matrix base on a quaternion and a position
	void SetOrientationAndPosition(const Quaternion& q, const Vector3D&p);

	//Transform a position
	Vector3D TransformPosition(const Vector3D& vector);

	//Transform a direction by ignoring the translation
	Vector3D TransformDirection(const Vector3D& vector);

};

