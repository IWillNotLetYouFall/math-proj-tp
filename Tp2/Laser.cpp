#include "Laser.h"

Laser::Laser()
{
	this->shape.setRadius(9.f);
	this->shape.setPointCount(4);
	this->shape.setFillColor(Color::Yellow);
	this->shape.setOrigin(4.5f, 4.5f);
}

Laser::Laser(const Laser& base)
{
	this->velocite = base.velocite;
	this->position = base.position;
	this->shape.setRadius(9.f);
	this->shape.setPointCount(4);
	this->shape.setFillColor(Color::Yellow);
	this->shape.setOrigin(4.5f, 4.5f);
}