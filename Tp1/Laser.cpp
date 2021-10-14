#include "Laser.h"

Laser::Laser() : Particule()
{
	maxSpeed = 2100;
	shape = new RectangleShape(Vector2f(50, 10));
	this->shape->setOrigin(radius / 2, radius / 2);
	this->shape->setFillColor(Color::Yellow);
}

Laser::Laser(const Laser& base) : Particule(base)
{
	maxSpeed = 1500;
	shape = new CircleShape(radius, 4);
	this->shape->setOrigin(radius / 2, radius / 2);
	this->shape->setFillColor(Color::Yellow);
}

void Laser::Integrate(float delta)
{
	Particule::Integrate(delta);
	float rad = std::atan2(velocite.Normalize().y, velocite.Normalize().x);
	float angle = (rad / 3.14f) * 180.0;
	shape->setRotation(angle);
}
