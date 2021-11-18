#include "SpringForceGenerator.h"

void SpringForceGenerator::UpdateForce(RigidBody* rigidBody)
{
	// Calculate the two ends in world space.
	Vector3D lws = rigidBody->TransformPoint(m_bodyAnchor);
	Vector3D ows = m_otherRigidBody->TransformPoint(m_otherBodyAnchor);

	// Calculate the vector of the spring.
	Vector3D force = lws - ows;

	// Calculate the magnitude of the force.
	//Norm^2 = magnitude
	float magnitude = pow(force.GetNorm(),2);
	magnitude = abs(magnitude - m_restLength);
	magnitude *= m_k;

	// Calculate the final force and apply it.
	force.Normalize();
	force *= -magnitude;
	rigidBody->AddForceAtPoint(force, lws);
}
