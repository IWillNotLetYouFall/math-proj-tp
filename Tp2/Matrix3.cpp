#include "Matrix3.h"

Matrix3::Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
    values[0] = a;
    values[1] = b;
    values[2] = c;
    values[3] = d;
    values[4] = e;
    values[5] = f;
    values[6] = g;
    values[7] = h;
    values[8] = i;
}

Matrix3 Matrix3::operator*(const Matrix3& other) const
{
    return Matrix3(
        values[0] * other.values[0] + values[1] * other.values[3] + values[2] * other.values[6],
        values[0] * other.values[1] + values[1] * other.values[4] + values[2] * other.values[7],
        values[0] * other.values[2] + values[1] * other.values[5] + values[2] * other.values[8],
        values[3] * other.values[0] + values[4] * other.values[3] + values[5] * other.values[6],
        values[3] * other.values[1] + values[4] * other.values[4] + values[5] * other.values[7],
        values[3] * other.values[2] + values[4] * other.values[5] + values[5] * other.values[8],
        values[6] * other.values[0] + values[7] * other.values[3] + values[8] * other.values[6],
        values[6] * other.values[1] + values[7] * other.values[4] + values[8] * other.values[7],
        values[6] * other.values[2] + values[7] * other.values[5] + values[8] * other.values[8]
    );
}

Vector3D Matrix3::operator*(const Vector3D& v) const
{
    Vector3D res;

    res.setX(values[0] * v.x + values[1] * v.y + values[2] * v.z);
    res.setY(values[3] * v.x + values[4] * v.y + values[5] * v.z);
    res.setZ(values[6] * v.x + values[7] * v.y + values[8] * v.z);

    return res;
}

Matrix3 Matrix3::Inverse()
{
    Matrix3 m;

    float t4 = m.values[0] * m.values[4];
    float t6 = m.values[0] * m.values[5];
    float t8 = m.values[1] * m.values[3];
    float t10 = m.values[2] * m.values[3];
    float t12 = m.values[1] * m.values[6];
    float t14 = m.values[2] * m.values[6];
    // Calculate the determinant.
    float t16 = (t4 * m.values[8] - t6 * m.values[7] - t8 * m.values[8] +
        t10 * m.values[7] + t12 * m.values[5] - t14 * m.values[4]);
    // Make sure the determinant is non-zero.
    if (t16 == 0.0f) return;
    float t17 = 1 / t16;
    values[0] = (m.values[4] * m.values[8] - m.values[5] * m.values[7]) * t17;
    values[1] = -(m.values[1] * m.values[8] - m.values[2] * m.values[7]) * t17;
    values[2] = (m.values[1] * m.values[5] - m.values[2] * m.values[4]) * t17;
    values[3] = -(m.values[3] * m.values[8] - m.values[5] * m.values[6]) * t17;
    values[4] = (m.values[0] * m.values[8] - t14) * t17;
    values[5] = -(t6 - t10) * t17;
    values[6] = (m.values[3] * m.values[7] - m.values[4] * m.values[6]) * t17;
    values[7] = -(m.values[0] * m.values[7] - t12) * t17;
    values[8] = (t4 - t8) * t17;

    return m;
}

Matrix3 Matrix3::Transpose()
{
    Matrix3 m;

    values[0] = m.values[0];
    values[1] = m.values[3];
    values[2] = m.values[6];
    values[3] = m.values[1];
    values[4] = m.values[4];
    values[5] = m.values[7];
    values[6] = m.values[2];
    values[7] = m.values[5];
    values[8] = m.values[8];

    return m;
}

void Matrix3::SetOrientation(Quaternion q)
{
    values[0] = 1 - (2*q.getJ()*q.getJ() + 2*q.getK()*q.getK());
    values[1] = 2*q.getI()*q.getJ() + 2*q.getK()*q.getW();
    values[2] = 2*q.getI()*q.getK() - 2*q.getJ()*q.getW();
    values[3] = 2*q.getI()*q.getJ() - 2*q.getK()*q.getW();
    values[4] = 1 - (2*q.getI()*q.getI() + 2*q.getK()*q.getK());
    values[5] = 2*q.getJ()*q.getK() + 2*q.getI()*q.getW();
    values[6] = 2*q.getI()*q.getK() + 2*q.getJ()*q.getW();
    values[7] = 2*q.getJ()*q.getK() - 2*q.getI()*q.getW();
    values[8] = 1 - (2*q.getI()*q.getI() + 2*q.getJ()*q.getJ());
}
