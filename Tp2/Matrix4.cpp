#include "Matrix4.h"

Matrix4 Matrix4::operator*(const Matrix4& other) const
{
    return Matrix4();
}

Vector3D Matrix4::operator*(const Vector3D& vector) const
{
    return Vector3D();
}

Matrix4 Matrix4::Inverse()
{
    return Matrix4();
}

void Matrix4::SetOrientationAndPosition(const Quaternion& q, const Vector3D& p)
{
}

Vector3D Matrix4::TransformPosition(const Vector3D& vector)
{
    return Vector3D();
}

Vector3D Matrix4::TransformDirection(const Vector3D& vector)
{
    return Vector3D();
}
