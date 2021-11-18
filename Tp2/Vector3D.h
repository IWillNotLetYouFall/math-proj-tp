#pragma once
#include <math.h>
#include <string>
#include <iomanip>
#include <sstream>

class Vector3D
{
public:
	float x; float y; float z;

public:
	Vector3D(float x = 0, float y = 0, float z = 0);
	Vector3D operator*(float value);
	Vector3D operator*=(float value);
	Vector3D operator/(float value);
	Vector3D operator/=(float value);
	Vector3D operator-(Vector3D value);
	Vector3D operator-=(Vector3D value);
	Vector3D operator+(Vector3D value);
	Vector3D operator+=(Vector3D value);
	void setX(float xx) { x = xx; }
	void setY(float yy) { x = yy; }
	void setZ(float zz) { x = zz; }
	float GetNorm();
	Vector3D Normalize();
	float ScalarProduct(Vector3D prod);
	Vector3D Product(Vector3D prod);
	Vector3D VectorialProduct(Vector3D prod);
	std::string ToString();
	Vector3D Inverse();
};

