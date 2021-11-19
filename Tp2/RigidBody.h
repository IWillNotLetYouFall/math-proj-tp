#pragma once
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "Matrix3.h"

class RigidBody
{
	//Other knowned RigidBody members

private:

	float inverseMasse = 1;

	//Linear Values
	float linearDamping;
	Vector3D acceleration;
	Vector3D position;
	Vector3D velocity;

	//Rotation Values
	Quaternion orientation;
	Vector3D rotation;
	Matrix4 transformMatrix;
	Vector3D angularAcceleration;

	Matrix3 inverseInertiaTensor;
	Matrix3 inverseInertiaTensorWorld;
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
	RigidBody(float masse);

	void Integrate(float duration);

	Vector3D getPointInWorldSpace(const Vector3D& point);

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

	void setMass(float mass) {
		if (mass >= 1000000) // infinite
		{
			inverseMasse = 0;
			return;
		}
		inverseMasse = 1 / mass;
	}

	Vector3D TransformPoint(Vector3D pos)
	{
		return pos.Inverse();
	}

	//Add force on the Center of mass (no torque generated)
	void AddForce(const Vector3D& force);
	void AddTorque(const Vector3D& torque);
	void setInertiaTensor(const Matrix3& inertiaTensor);

	//Add force at a point in world coordinate.
	//Generate force and torque
	void AddForceAtPoint(const Vector3D& force, const Vector3D& LocalPoint);

	void AddForceAtBodyPoint(const Vector3D& force, const Vector3D& point);

	//called each frame to reset m_forceAccum and m_torqueAccum
	void ClearAccumulator();
};