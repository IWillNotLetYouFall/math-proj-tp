#pragma once
#include "Vector3D.h"
#include "Quaternion.h"
class Matrix3
{
private:
	//values of the matrix3
	float values[9];

public:
	Matrix3() { for (int i = 0; i < 9; i++) values[i] = 0; };
	Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i);

	//combination of linear transformation
	Matrix3 operator*(const Matrix3& other) const;

	//Transform of a vector
	Vector3D operator* (const Vector3D& v) const;

	//Get the Inverse matrix
	Matrix3 Inverse();

	//Get the Transpose matrix
	Matrix3 Transpose();

	//Set the matrix base on a quaternion
	void SetOrientation(Quaternion q);
};

