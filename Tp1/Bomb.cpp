#include "Bomb.h"

Bomb::Bomb() : Particule()
{
	maxSpeed = 700;
	shape = new CircleShape(radius);
	this->shape->setOrigin(radius / 2, radius / 2);
	Color color = Color(117, 117, 117);
	this->shape->setFillColor(color);

	Physics::GetInstance()->AddCircle(dynamic_cast<CircleShape*>(shape));
}

Bomb::Bomb(const Bomb& base) : Particule(base)
{
	maxSpeed = 700;
	shape = new CircleShape(radius);
	this->shape->setOrigin(radius / 2, radius / 2);
	Color color = Color(117, 117, 117);
	this->shape->setFillColor(color);
}

void Bomb::Integrate(float delta)
{
	//TODO: Ajout récursivité collision
	Contact* contact = Physics::GetInstance()->CollisionDetection(shape, masse, velocite, delta);

	//TODO : CONTACT RESOLUTION
	if (contact != NULL) {
		Vector3D ligneContact = contact->contactPos - position;
		float distContact = (radius - ligneContact.GetNorm());
		Vector3D normLine = ligneContact.Normalize();
		Vector3D ligneDecalage = normLine * distContact;

		position -= ligneDecalage;
	}

	Particule::Integrate(delta);
}