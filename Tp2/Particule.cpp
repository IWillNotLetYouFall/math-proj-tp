#include "Particule.h"

Particule::Particule()
{
	this->shape.setRadius(5);
	this->shape.setFillColor(Color::White);
	this->shape.setOrigin(2.5f, 2.5f);
}

Particule::Particule(const Particule& base)
{
	this->velocite = base.velocite;
	this->position = base.position;
	this->shape.setRadius(5);
	this->shape.setFillColor(Color::White);
	this->shape.setOrigin(2.5f, 2.5f);
}

Particule::~Particule()
{
}

void Particule::Integrate(float delta)
{
	//MAJ Position
	position += (velocite * delta);

	//MAJ velocit�
	velocite = (velocite * damping) + acceleration * delta;

	shape.setPosition(position.x, position.y);
}

void Particule::SetMasse(float masse)
{
	this->masse = masse;
}

float Particule::InverseMasse()
{
	if (masse >= masseMax) return 0;
	return 1 / masse;
}

void Particule::addForce(const Vector3D& force)
{
	forceAcc += force;
}

void Particule::clearForceAcc()
{
	forceAcc.x = 0;
	forceAcc.y = 0;
	forceAcc.z = 0;
}