#include "Matrix3.h"

Matrix3 Matrix3::operator*(const Matrix3& other) const
{
    return Matrix3();
}

Vector3D Matrix3::operator*(const Vector3D& vector) const
{
    return Vector3D();
}

Matrix3 Matrix3::Inverse()
{
    return Matrix3();
}

Matrix3 Matrix3::Transpose()
{
    return Matrix3();
}

void Matrix3::SetOrientation(const Quaternion& q)
{
}
