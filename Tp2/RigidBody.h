#pragma once
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix4.h"

class RigidBody
{
	//Other knowned RigidBody members

private:

	float inverseMasse;

	//Linear Values
	float linearDamping;
	Vector3D position;
	Vector3D velocity;

	//Rotation Values
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

	Vector3D getPointInWorldSpace(const Vector3D& point);

public:
	void Integrate(float duration);

	bool hasInfiniteMass() 
	{ 
		if (inverseMasse == 0) 
			return true; 
		return false; 
	};

	float getMass() 
	{ 
		if (inverseMasse == 0)
			return 100000;
		return 1 / inverseMasse; 
	};

	Vector3D TransformPoint(Vector3D pos)
	{
		return pos.Inverse();
	}

	//Add force on the Center of mass (no torque generated)
	void AddForce(const Vector3D& force);
	void AddTorque(const Vector3D& torque);

	//Add force at a point in world coordinate.
	//Generate force and torque
	void AddForceAtPoint(const Vector3D& force, const Vector3D& LocalPoint);

	void AddForceAtBodyPoint(const Vector3D& force, const Vector3D& point);

	//called each frame to reset m_forceAccum and m_torqueAccum
	void ClearAccumulator();
};