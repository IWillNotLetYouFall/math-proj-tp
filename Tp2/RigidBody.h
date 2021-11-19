#pragma once
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "Matrix3.h"
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>

using namespace sf;

class RigidBody
{
	//Other knowned RigidBody members

private:

	float inverseMasse = 1;

	//Linear Values
	float linearDamping = 0.2f;
	Vector3D acceleration;
	Vector3D position;
	Vector3D velocity;
	float maxSpeed = 320.f;

	//Rotation Values
	Quaternion orientation;
	Vector3D rotation;
	Matrix4 transformMatrix;
	Vector3D angularAcceleration;

	Matrix3 inverseInertiaTensor;
	Matrix3 inverseInertiaTensorWorld;
	//same as linear damping
	//but for rotation
	float m_angularDamping = 0.2f;

	//Accumulated force
	//added by ForceGenerator
	Vector3D m_forceAccum;

	//Accumulated torque
	//added by ForceGenerator
	Vector3D m_torqueAccum;

	void CalculateDerivedData();

public:

	RectangleShape shape;
	float damping = 0.2f;
	bool test = false;

	RigidBody(float masse);
	RigidBody(Color color, float radius);

	void Integrate(float duration);

	Vector3D getPointInWorldSpace(const Vector3D& point);

	bool hasInfiniteMass() 
	{ 
		if (inverseMasse == 0) 
			return true; 
		return false; 
	};

	void SetMaxSpeed(float speed)
	{
		this->maxSpeed = speed;
	};

	void SetPosition(Vector3D pos)
	{
		this->position = pos;
		shape.setPosition(pos.x, pos.y);
	};

	Vector3D GetPosition()
	{
		return this->position;
	};

	Vector3D GetScale()
	{
		Vector2f scale = shape.getSize();
		return Vector3D(scale.x, scale.y, 1);
	};

	void SetScale(Vector3D scale)
	{
		shape.setSize(Vector2f(scale.x, scale.y));
		this->shape.setOrigin(scale.x / 2, scale.y / 2);
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