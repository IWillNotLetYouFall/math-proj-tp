#include "Particule.h"

Particule::Particule()
{
	this->shape = new CircleShape(7.f);
	this->velocite = Vector3D();
	this->position = Vector3D();
	acceleration = Vector3D(0, 14);
}

Particule::Particule(const Particule& base)
{
	this->shape = new CircleShape(7.f);
	this->velocite = base.velocite;
	this->position = base.position;
}

Particule::~Particule()
{
}

void Particule::Integrate(float delta)
{
	//MAJ Position
	position += (velocite * delta);

	//MAJ velocit?
	acceleration.y = acceleration.y - 6.f * (damping * masse);
	velocite -= acceleration * delta;

	shape->setPosition(position.x, position.y);
}

void Particule::SetMasse(float masse)
{
	this->masse = masse;
}

float Particule::InverseMasse()
{
	return 1 / masse;
}

void Particule::Draw(RenderWindow* window)
{
	//TODO : POGGG
	window->draw(*shape);
}
