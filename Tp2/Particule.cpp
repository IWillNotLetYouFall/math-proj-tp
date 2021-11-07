#include "Particule.h"
#include <iostream>

Particule::Particule()
{
	this->shape.setRadius(5);
	this->shape.setFillColor(Color::White);
	this->shape.setOrigin(2.5f, 2.5f);
}

Particule::Particule(Color color, float radius)
{
	this->shape.setRadius(radius);
	this->shape.setFillColor(color);
	this->shape.setOrigin(radius, radius);
}

Particule::~Particule()
{
}

void Particule::Integrate(float delta)
{

	//Apply max mouv
	if (velocite.GetNorm() > maxSpeed) 
		velocite = velocite.Normalize() * maxSpeed;

	//MAJ Position
	position += (velocite * delta);
	shape.setPosition(position.x, position.y);

	//MAJ velocité
	velocite += forceAcc * delta;
	velocite *= powf(damping, delta);
}

void Particule::SetMaxSpeed(float speed)
{
	this->maxSpeed = speed;
}

void Particule::SetMasse(float masse)
{
	this->masse = masse;
}

float Particule::InverseMasse()
{
	//if (masse >= masseMax) return 0;
	return 1 / masse;
}

void Particule::addForce(const Vector3D& force)
{
	forceAcc += force;
}

float Particule::GetRadius()
{
	return shape.getRadius();
}

void Particule::SetRadius(float radius)
{
	shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
}

void Particule::clearForceAcc()
{
	forceAcc.x = 0;
	forceAcc.y = 0;
	forceAcc.z = 0;
}