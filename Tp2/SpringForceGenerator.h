#pragma once
#include "ForceGeneratorBody.h"

class SpringForceGenerator : public ForceGeneratorBody
{
private:
	//Anchor point in Local coordinate.
	Vector3D m_body_anchor;

	RigidBody* m_otherRigidBody = nullptr;
	//Other anchor point in other's Local coordinate.
	Vector3D m_otherBodyAnchor;

	//spring parameters
	float m_k;
	float m_restLength;

public:
	//Transform each anchor point in world coordinate.
	//calculate the spring force and apply it at anchor point.
	void UpdateForce(RigidBody* rigidBody) override;
};