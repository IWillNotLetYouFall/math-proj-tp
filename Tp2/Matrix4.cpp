#include "Matrix4.h"

Matrix4 Matrix4::operator*(const Matrix4& other) const
{
    Matrix4 result;
    result.values[0] = (other.values[0] * values[0]) + (other.values[4] * values[1]) +
        (other.values[8] * values[2]);
    result.values[4] = (other.values[0] * values[4]) + (other.values[4] * values[5]) +
        (other.values[8] * values[6]);
    result.values[8] = (other.values[0] * values[8]) + (other.values[4] * values[9]) +
        (other.values[8] * values[10]);
    result.values[1] = (other.values[1] * values[0]) + (other.values[5] * values[1]) +
        (other.values[9] * values[2]);
    result.values[5] = (other.values[1] * values[4]) + (other.values[5] * values[5]) +
        (other.values[9] * values[6]);
    result.values[9] = (other.values[1] * values[8]) + (other.values[5] * values[9]) +
        (other.values[9] * values[10]);
    result.values[2] = (other.values[2] * values[0]) + (other.values[6] * values[1]) +
        (other.values[10] * values[2]);
    result.values[6] = (other.values[2] * values[4]) + (other.values[6] * values[5]) +
        (other.values[10] * values[6]);
    result.values[10] = (other.values[2] * values[8]) + (other.values[6] * values[9]) +
        (other.values[10] * values[10]);
    result.values[3] = (other.values[3] * values[0]) + (other.values[7] * values[1]) +
        (other.values[11] * values[2]) + values[3];
    result.values[7] = (other.values[3] * values[4]) + (other.values[7] * values[5]) +
        (other.values[11] * values[6]) + values[7];
    result.values[11] = (other.values[3] * values[8]) + (other.values[7] * values[9]) +
        (other.values[11] * values[10]) + values[11];

    return result;
}

Vector3D Matrix4::operator*(const Vector3D& vector) const
{
    return Vector3D(
        vector.x * values[0] +  vector.y * values[1] + vector.z * values[2] + values[3],
        vector.x * values[4] + vector.y * values[5] + vector.z * values[6] + values[7],
        vector.x * values[8] + vector.y * values[9] + vector.z * values[10] + values[11]
    );
}

float Matrix4::GetDeterminant() const
{
    return values[8] * values[5] * values[2] +
        values[4] * values[9] * values[2] +
        values[8] * values[1] * values[6] -
        values[0] * values[9] * values[6] -
        values[4] * values[1] * values[10] +
        values[0] * values[5] * values[10];
}

Matrix4 Matrix4::Inverse()
{
    float det = GetDeterminant();
    if (det == 0)
    {
        return Matrix4();
    }

    Matrix4 m;
    det = 1.0f / det;

    values[0] = (-m.values[9] * m.values[6] + m.values[5] * m.values[10]) * det;
    values[4] = (m.values[8] * m.values[6] - m.values[4] * m.values[10]) * det;
    values[8] = (-m.values[8] * m.values[5] + m.values[4] * m.values[9]) * det;
    values[1] = (m.values[9] * m.values[2] - m.values[1] * m.values[10]) * det;
    values[5] = (-m.values[8] * m.values[2] + m.values[0] * m.values[10]) * det;
    values[9] = (m.values[8] * m.values[1] - m.values[0] * m.values[9]) * det;
    values[2] = (-m.values[5] * m.values[2] + m.values[1] * m.values[6]) * det;
    values[6] = (+m.values[4] * m.values[2] - m.values[0] * m.values[6]) * det;
    values[10] = (-m.values[4] * m.values[1] + m.values[0] * m.values[5]) * det;
    values[3] = (m.values[9] * m.values[6] * m.values[3]
        - m.values[5] * m.values[10] * m.values[3]
        - m.values[9] * m.values[2] * m.values[7]
        + m.values[1] * m.values[10] * m.values[7]
        + m.values[5] * m.values[2] * m.values[11]
        - m.values[1] * m.values[6] * m.values[11]) * det;
    values[7] = (-m.values[8] * m.values[6] * m.values[3]
        + m.values[4] * m.values[10] * m.values[3]
        + m.values[8] * m.values[2] * m.values[7]
        - m.values[0] * m.values[10] * m.values[7]
        - m.values[4] * m.values[2] * m.values[11]
        + m.values[0] * m.values[6] * m.values[11]) * det;
    values[11] = (m.values[8] * m.values[5] * m.values[3]
        - m.values[4] * m.values[9] * m.values[3]
        - m.values[8] * m.values[1] * m.values[7]
        + m.values[0] * m.values[9] * m.values[7]
        + m.values[4] * m.values[1] * m.values[11]
        - m.values[0] * m.values[5] * m.values[11]) * det;
    return m;
}

void Matrix4::SetOrientationAndPosition(Quaternion q, const Vector3D& p)
{
    values[0] = 1 - (2 * q.getJ() * q.getJ() + 2 * q.getK() * q.getK());
    values[1] = 2 * q.getI() * q.getJ() + 2 * q.getK() * q.getW();
    values[2] = 2 * q.getI() * q.getK() - 2 * q.getJ() * q.getW();
    values[3] = p.x;
    values[4] = 2 * q.getI() * q.getJ() - 2 * q.getK() * q.getW();
    values[5] = 1 - (2 * q.getI() * q.getI() + 2 * q.getK() * q.getK());
    values[6] = 2 * q.getJ() * q.getK() + 2 * q.getI() * q.getW();
    values[7] = p.y;
    values[8] = 2 * q.getI() * q.getK() + 2 * q.getJ() * q.getW();
    values[9] = 2 * q.getJ() * q.getK() - 2 * q.getI() * q.getW();
    values[10] = 1 - (2 * q.getI() * q.getI() + 2 * q.getJ() * q.getJ());
    values[11] = p.z;
}

Vector3D Matrix4::TransformPosition(const Vector3D& vector)
{
    Vector3D v = *this * vector;
    return v;
}

Vector3D Matrix4::TransformDirection(const Vector3D& vector)
{
    return Vector3D(
        vector.x * values[0] +
        vector.y * values[1] +
        vector.z * values[2],
        vector.x * values[4] +
        vector.y * values[5] +
        vector.z * values[6],
        vector.x * values[8] +
        vector.y * values[9] +
        vector.z * values[10]
    );
}
