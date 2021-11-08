#pragma once
#include "ForceGeneratorBody.h"

class GravityForceGeneratorBody : public ForceGeneratorBody
{
private:
	Vector3D m_gravity;

public:
	//Apply the gravity force to center of mass of the rigidBody
	void UpdateForce(RigidBody* rigidbody) override;
};