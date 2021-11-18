#include "Vector3D.h"

Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D Vector3D::operator*(float value)
{
	return Vector3D(x * value, y * value, z * value);
}

Vector3D Vector3D::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;
	return Vector3D(x, y, z);
}

Vector3D Vector3D::operator/(float value)
{
	return Vector3D(x / value, y / value, z / value);
}

Vector3D Vector3D::operator/=(float value)
{
	x /= value;
	y /= value;
	z /= value;
	return Vector3D(x, y, z);
}

Vector3D Vector3D::operator-(Vector3D value)
{
	return Vector3D(x - value.x, y - value.y, z - value.z);
}

Vector3D Vector3D::operator-=(Vector3D value)
{
	x -= value.x;
	y -= value.y;
	z -= value.z;
	return Vector3D(x, y, z);
}

Vector3D Vector3D::operator+(Vector3D value)
{
	return Vector3D(x + value.x, y + value.y, z + value.z);
}

Vector3D Vector3D::operator+=(Vector3D value)
{
	x += value.x;
	y += value.y;
	z += value.z;
	return Vector3D(x, y, z);
}

float Vector3D::GetNorm()
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

Vector3D Vector3D::Normalize()
{
	float norm = GetNorm();
	return Vector3D(x / norm, y / norm, z / norm);
}

float Vector3D::ScalarProduct(Vector3D prod)
{
	return (x * prod.x) + (y * prod.y) + (z * prod.z);
}

Vector3D Vector3D::Product(Vector3D prod)
{
	x *= prod.x;
	y *= prod.y;
	z *= prod.z;
	return Vector3D(x, y, z);
}

Vector3D Vector3D::VectorialProduct(Vector3D prod)
{
	return Vector3D(
		(y * prod.z) - (z * prod.y),
		(z * prod.x) - (x * prod.z),
		(x * prod.y) - (y * prod.x)
	);
}

std::string Vector3D::ToString()
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << x << "," << y << "," << z;
	return "V(" + stream.str() + ")";
}

Vector3D Vector3D::Inverse()
{
	return Vector3D(-x, -y, -z);
}
