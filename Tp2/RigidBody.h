#pragma once
#include "Vector3D.h"

class RigidBody
{
	//Other knowned RigidBody members

private:

	//same as linear damping
	//but for rotation
	float m_angularDamping;

	//Accumulated force
	//added by ForceGenerator
	Vector3D m_forceAccum;

	//Accumulated torque
	//added by ForceGenerator
	Vector3D m_torqueAccum;

public:

	//Add force on the Center of mass (no torque generated)
	void AddForce(const Vector3D& force);

	//Add force at a point in world coordiante.
	//Geneerate force and torque
	void AddForceAtPoint(const Vector3D& force, const Vector3D& LocalPoint);

	//called each frame to reset m_forceAccum and m_torqueAccum
	void ClearAccumulator();
};