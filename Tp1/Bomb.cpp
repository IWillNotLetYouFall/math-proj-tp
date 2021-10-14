#include "Bomb.h"

Bomb::Bomb() : Particule()
{
	maxSpeed = 700;
	shape = new CircleShape(radius);
	this->shape->setOrigin(radius / 2, radius / 2);
	Color color = Color(117, 117, 117);
	this->shape->setFillColor(color);
}

Bomb::Bomb(const Bomb& base) : Particule(base)
{
	maxSpeed = 700;
	shape = new CircleShape(radius);
	this->shape->setOrigin(radius / 2, radius / 2);
	Color color = Color(117, 117, 117);
	this->shape->setFillColor(color);
}