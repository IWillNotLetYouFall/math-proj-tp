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
