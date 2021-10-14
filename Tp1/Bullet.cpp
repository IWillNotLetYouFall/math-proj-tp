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