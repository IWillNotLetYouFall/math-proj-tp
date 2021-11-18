#include "RigidBody.h"

void RigidBody::CalculateDerivedData()
{
	transformMatrix.setValue(0, 1 - 2 * orientation.getJ() * orientation.getJ() - 2 * orientation.getK() * orientation.getK());
	transformMatrix.setValue(1, 2 * orientation.getI() * orientation.getJ() - 2 * orientation.getW() * orientation.getK());
	transformMatrix.setValue(2, 2 * orientation.getI() * orientation.getK() + 2 * orientation.getW() * orientation.getJ());
	transformMatrix.setValue(3, position.x);
	transformMatrix.setValue(4, 2 * orientation.getI() * orientation.getJ() + 2 * orientation.getW() * orientation.getK());
	transformMatrix.setValue(5, 1 - 2 * orientation.getI() * orientation.getI() - 2 * orientation.getK() * orientation.getK());
	transformMatrix.setValue(6, 2 * orientation.getJ() * orientation.getK() - 2 * orientation.getW() * orientation.getI());
	transformMatrix.setValue(7, position.y);
	transformMatrix.setValue(8, 2 * orientation.getI() * orientation.getK() - 2 * orientation.getW() * orientation.getJ());
	transformMatrix.setValue(9, 2 * orientation.getJ() * orientation.getK() + 2 * orientation.getW() * orientation.getI());
	transformMatrix.setValue(10, 1 - 2 * orientation.getI() * orientation.getI() - 2 * orientation.getJ() * orientation.getJ());
	transformMatrix.setValue(11, position.z);
}

Vector3D RigidBody::getPointInWorldSpace(const Vector3D& point)
{
	return orientation * ((Vector3D)point + position);
}

void RigidBody::Integrate(float duration)
{






	ClearAccumulator();
}

void RigidBody::AddForce(const Vector3D& force)
{
	m_forceAccum += force;
}

void RigidBody::AddTorque(const Vector3D& torque)
{
	m_torqueAccum += torque;
}

void RigidBody::AddForceAtPoint(const Vector3D& force, const Vector3D& LocalPoint)
{
	m_forceAccum += force;

	Vector3D f = force;
	m_torqueAccum += f.VectorialProduct(LocalPoint);
}

void RigidBody::AddForceAtBodyPoint(const Vector3D& force, const Vector3D& point)
{
	Vector3D worldP = getPointInWorldSpace(point);
	AddForceAtPoint(force, point);
}

void RigidBody::ClearAccumulator()
{
	m_forceAccum.x = 0;
	m_forceAccum.y = 0;
	m_forceAccum.z = 0;

	m_torqueAccum.x = 0;
	m_torqueAccum.y = 0;
	m_torqueAccum.z = 0;
}
