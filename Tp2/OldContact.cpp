#include "OldContact.h"

OldContact::OldContact(Collider* collider, Collider* collided, Vector3D contactPos)
{
	this->collider = collider;
	this->collided = collided;
	this->contactPos = contactPos;
}
