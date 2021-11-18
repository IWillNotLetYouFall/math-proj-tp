#pragma once
#include "Vector3D.h"
#include "Quaternion.h"
class Matrix4
{
private:
	//values of the matrix3
	float values[12];

	float GetDeterminant() const;

public:

	//combination of linear transformation
	Matrix4 operator*(const Matrix4& other) const;

	//Transform of a vector
	Vector3D operator* (const Vector3D& vector) const;

	//Get the Inverse matrix
	Matrix4 Inverse();

	void setValue(int index, float value)
	{
		if (index > 11 || index < 0) return;
		values[index] = value;
	};

	//Set the matrix base on a quaternion and a position
	void SetOrientationAndPosition(Quaternion q, const Vector3D& p);

	//Transform a position
	Vector3D TransformPosition(const Vector3D& vector);

	//Transform a direction by ignoring the translation
	Vector3D TransformDirection(const Vector3D& vector);

};

