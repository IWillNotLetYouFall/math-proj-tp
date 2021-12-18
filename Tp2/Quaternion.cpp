#include "Quaternion.h"

void Quaternion::Normalized()
{
	float d = 0;
	for (int i = 0; i < 4; i++)
	{
		d += value[i] * value[i];
	}

	// Check for zero length quaternion, and use the no-rotation
	// quaternion in that case.
	if (d == 0) {
		value[0] = 1;
		return;
	}

	d = 1.0f / (sqrtf(d));
	value[0] *= d;
	value[1] *= d;
	value[2] *= d;
	value[3] *= d;
}

Quaternion Quaternion::operator*(const Quaternion& other)
{
	Quaternion q = *this;
	value[0] = q.value[0] * other.value[0] - q.value[1] * other.value[1] -
		q.value[2] * other.value[2] - q.value[3] * other.value[3];
	value[1] = q.value[0] * other.value[1] + q.value[1] * other.value[0] +
		q.value[2] * other.value[3] - q.value[3] * other.value[2];
	value[2] = q.value[0] * other.value[2] + q.value[2] * other.value[0] +
		q.value[3] * other.value[1] - q.value[1] * other.value[3];
	value[3] = q.value[0] * other.value[3] + q.value[3] * other.value[0] +
		q.value[1] * other.value[2] - q.value[2] * other.value[1];
	return Quaternion(value[0], value[1], value[2], value[3]);
}

Vector3D Quaternion::operator*(const Vector3D& vec)
{
	float num = getI() * 2.f;
	float num2 = getJ() * 2.f;
	float num3 = getK() * 2.f;
	float num4 = getI() * num;
	float num5 = getJ() * num2;
	float num6 = getK() * num3;
	float num7 = getI() * num2;
	float num8 = getI() * num3;
	float num9 = getJ() * num3;
	float num10 = getW() * num;
	float num11 = getW() * num2;
	float num12 = getW() * num3;
	Vector3D result;
	result.x = (1.f - (num5 + num6)) * vec.x + (num7 - num12) * vec.y + (num8 + num11) * vec.z;
	result.y = (num7 + num12) * vec.x + (1.f - (num4 + num6)) * vec.y + (num9 - num10) * vec.z;
	result.z = (num8 - num11) * vec.x + (num9 + num10) * vec.y + (1.f - (num4 + num5)) * vec.z;
	return result;
}

void Quaternion::RotateByVector(const Vector3D& vector, float duration)
{
	Quaternion q(0, vector.x * duration, vector.y * duration, vector.z * duration);
	*this = (*this) * q;
}

void Quaternion::addScaledVector(const Vector3D& vector, float scale)
{
	Quaternion q(0,
		vector.x * scale,
		vector.y * scale,
		vector.z * scale);
	q = q * *this;
	value[0] += q.getW();
	value[1] += q.getI();
	value[2] += q.getJ();
	value[3] += q.getK();
}

void Quaternion::UpdateByAngularVelocity(const Vector3D& rotation, float duration)
{
	Quaternion q(0, rotation.x * duration, rotation.y * duration, rotation.z * duration);
	q = q * (*this);
	value[0] += q.getW() * (0.5f);
	value[1] += q.getI() * (0.5f);
	value[2] += q.getJ() * (0.5f);
	value[3] += q.getK() * (0.5f);
}

Vector3D Quaternion::GetEulerAngles()
{
	float w, x, y, z;

	w = value[0];
	x = value[1];
	y = value[2];
	z = value[3];

	float sqw = w * w;
	float sqx = x * x;
	float sqy = y * y;
	float sqz = z * z;

	Vector3D dirEuler;
	dirEuler.x = (float)(atan2(2.0 * (x * y + z * w), (sqx - sqy - sqz + sqw)) * (180.0f / 3.1415926f));
	dirEuler.z = (float)(atan2(2.0 * (y * z + x * w), (-sqx - sqy + sqz + sqw)) * (180.0f / 3.1415926f));
	dirEuler.y = (float)(asin(-2.0 * (x * z - y * w)) * (180.0f / 3.1415926f));

	return dirEuler;
}
