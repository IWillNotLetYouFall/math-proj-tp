#include "GravityForceGeneratorBody.h"

void GravityForceGeneratorBody::UpdateForce(RigidBody* rigidbody)
{
	if (rigidbody->hasInfiniteMass()) return;
	// Apply the mass-scaled force to the body
	rigidbody->AddForce(m_gravity * rigidbody->getMass());
}
