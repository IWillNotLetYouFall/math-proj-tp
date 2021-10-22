#include "Fireball.h"

Fireball::Fireball() : Particule()
{
	maxSpeed = 850;
	shape = new CircleShape(radius, 6);
	this->shape->setOrigin(radius / 2, radius / 2);
	this->shape->setFillColor(Color::Red);
}

Fireball::Fireball(const Fireball& base) : Particule(base)
{
	maxSpeed = 850;
	shape = new CircleShape(radius, 6);
	this->shape->setOrigin(radius / 2, radius / 2);
	this->shape->setFillColor(Color::Red);
}

void Fireball::Integrate(float delta)
{
	//TODO: Ajout récursivité collision
	Contact* contact = Physics::GetInstance().CollisionDetection(shape, masse, velocite, delta);
	
	//TODO : CONTACT RESOLUTION
	//Vector3D ligneContact = contact->contactPos - position;
	//float distContact = (radius - ligneContact.GetNorm());
	//Vector3D normLine = ligneContact.Normalize();
	//Vector3D ligneDecalage = normLine * distContact;
	//
	//position -= ligneDecalage;
	//


	Particule::Integrate(delta);
}
