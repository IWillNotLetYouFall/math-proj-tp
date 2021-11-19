#pragma once
#include "Vector3D.h";


class Quaternion
{
private:
	//w, i,j,k
	float value[4];

public:
	Quaternion() { value[0] = 1; value[1] = 0; value[2] = 0; value[3] = 0; };
	Quaternion(float a, float b, float c, float d) 
	{ 
		value[0] = a; value[1] = b; value[2] = c; value[3] = d; 
		float e = 0;
		for (int i = 0; i < 4; i++)
		{
			e += value[i] * value[i];
		}

		if (e == 0)
		{
			value[0] = 1; value[1] = 0; value[2] = 0; value[3] = 0;
		}
	};

	//normalize by multipling the quaternion by the inverse of the mass
	void Normalized();

	float getW() { return value[0]; };
	float getI() { return value[1]; };
	float getJ() { return value[2]; };
	float getK() { return value[3]; };

	//Quternion multiplication
	Quaternion operator*(const Quaternion& other);

	Vector3D operator*(const Vector3D& vec);

	void addScaledVector(const Vector3D& vector, float scale);

	//Rotate the quaternion by a vector - multiply this by q = (0, dx, dy, dz)
	void RotateByVector(const Vector3D& vector, float duration = 2);

	//Apply the quaternion update by the angular velocity
	void UpdateByAngularVelocity(const Vector3D& rotation, float duration);

	Vector3D GetEulerAngles();
};

