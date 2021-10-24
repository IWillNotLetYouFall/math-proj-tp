#include "Bullet.h"

Bullet::Bullet() : Particule()
{
	maxSpeed = 1100;
	shape = new CircleShape(radius);
	this->shape->setOrigin(radius / 2, radius / 2);
	this->shape->setFillColor(Color::Blue);
}

Bullet::Bullet(const Bullet& base) : Particule(base)
{
	maxSpeed = 1100;
	shape = new CircleShape(radius);
	this->shape->setOrigin(radius / 2, radius / 2);
	this->shape->setFillColor(Color::Blue);
}

void Bullet::Integrate(float delta)
{
	//TODO: Ajout récursivité collision
	
	//physic.CollisionDetection(shape, masse, velocite, delta);
	// 
	//Contact* contact = Physics::instance->CollisionDetection(shape, masse, velocite, delta);
	//
	////TODO : CONTACT RESOLUTION
	//Vector3D ligneContact = contact->contactPos - position;
	//float distContact = (radius - ligneContact.GetNorm());
	//Vector3D normLine = ligneContact.Normalize();
	//Vector3D ligneDecalage = normLine * distContact;
	//
	//position -= ligneDecalage;



	Particule::Integrate(delta);
}
