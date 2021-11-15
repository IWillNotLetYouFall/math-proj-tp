#pragma once
#include "Vector3D.h"
#include "Quaternion.h"
class Matrix3
{
private:
	//values of the matrix3
	float values[9];

public:
	//combination of linear transformation
	Matrix3 operator*(const Matrix3& other) const;

	//Transform of a vector
	Vector3D operator* (const Vector3D& vector) const;

	//Get the Inverse matrix
	Matrix3 Inverse();

	//Get the Transpose matrix
	Matrix3 Transpose();

	//Set the matrix base on a quaternion
	void SetOrientation(const Quaternion& q);
};

