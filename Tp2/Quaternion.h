#pragma once
#include "Vector3D.h";


class Quaternion
{
private:
	//w, i,j,k
	float value[4];

public:
	//normalize by multipling the quaternion by the inverse of the mass
	void Normalized();

	//Quternion multiplication
	Quaternion operator*(const Quaternion& other);

	//Rotate the quaternion by a vector - multiply this by q = (0, dx, dy, dz)
	void RotateByVector(const Vector3D& vector);

	//Apply the quaternion update by the angular velocity
	void UpdateByAngularVelocity(const Vector3D& rotation, float duration);
};

