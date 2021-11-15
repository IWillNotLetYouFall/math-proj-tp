#pragma once
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix4.h"

class RigidBody
{
	//Other knowned RigidBody members

private:

	float inverseMasse;
	float linearDamping;
	Vector3D position;
	Vector3D velocity;

	Quaternion orientation;
	Vector3D rotation;
	Matrix4 transformMatrix;
	//same as linear damping
	//but for rotation
	float m_angularDamping;

	//Accumulated force
	//added by ForceGenerator
	Vector3D m_forceAccum;

	//Accumulated torque
	//added by ForceGenerator
	Vector3D m_torqueAccum;

	void CalculateDerivedData();

public:
	void Integrate(float duration);

	//Add force on the Center of mass (no torque generated)
	void AddForce(const Vector3D& force);

	//Add force at a point in world coordiante.
	//Geneerate force and torque
	void AddForceAtPoint(const Vector3D& force, const Vector3D& LocalPoint);

	//called each frame to reset m_forceAccum and m_torqueAccum
	void ClearAccumulator();
};