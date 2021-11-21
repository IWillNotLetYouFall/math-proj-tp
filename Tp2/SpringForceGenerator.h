#pragma once
#include "ForceGeneratorBody.h"
#include <iostream>

class SpringForceGenerator : public ForceGeneratorBody
{
private:
	//Anchor point in Local coordinate.
	Vector3D m_bodyAnchor;

	RigidBody* m_otherRigidBody = nullptr;
	//Other anchor point in other's Local coordinate.
	Vector3D m_otherBodyAnchor;

	//spring parameters
	float m_k;
	float m_restLength;

public:

	SpringForceGenerator(const Vector3D& localConnectionPt,
		RigidBody* other,
		const Vector3D& otherConnectionPt,
		float springConstant,
		float restLength) :
		m_bodyAnchor(localConnectionPt),
		m_otherRigidBody(other),
		m_otherBodyAnchor(otherConnectionPt),
		m_k(springConstant),
		m_restLength(restLength) {};


	//Transform each anchor point in world coordinate.
	//calculate the spring force and apply it at anchor point.
	void UpdateForce(RigidBody* rigidBody) override;
};