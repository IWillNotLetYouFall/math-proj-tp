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
}

void Quaternion::RotateByVector(const Vector3D& vector, float duration)
{
	Quaternion q(0, vector.x * duration, vector.y * duration, vector.z * duration);
	*this = (*this) * q;
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
