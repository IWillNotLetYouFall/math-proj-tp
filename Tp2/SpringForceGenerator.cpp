#include "SpringForceGenerator.h"

void SpringForceGenerator::UpdateForce(RigidBody* rigidBody)
{
	// Calculate the two ends in world space.
	Vector3D lws = rigidBody->getPointInWorldSpace(m_bodyAnchor);
	Vector3D ows = m_otherRigidBody->getPointInWorldSpace(m_otherBodyAnchor);

	//std::cout << "Body Anchor : " + lws.ToString() + " | Other Anchor : " + ows.ToString() << std::endl;

	// Calculate the vector of the spring.
	Vector3D force = lws - ows;

	// Calculate the magnitude of the force.
	//Norm^2 = magnitude
	float magnitude = force.GetNorm();
	magnitude = abs(magnitude - m_restLength);
	magnitude *= m_k;

	// Calculate the final force and apply it.
	force.Normalize();
	force *= -magnitude;

	//std::cout << "Spring Force : " + force.ToString() + " | Spring Point : " + lws.ToString() << std::endl;
	rigidBody->AddForceAtPoint(force, lws);
}
