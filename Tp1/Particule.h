#pragma once
#include "Vector3D.h"
#include <cmath>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include "Physics.h"
#include "Contact.h"

using namespace sf;

class Particule
{
private:
	float masse = 3;
	Vector3D velInitiale = Vector3D(1, 1, 0);
	float damping = 0.995f;

	Vector3D forceAcc;

public:
	Shape* shape;
	Vector3D position;
	Vector3D velocite;
	Vector3D acceleration = Vector3D(0,1000,0);
	float maxSpeed = 600.f;

public:
	Particule();
	Particule(const Particule& base);
	~Particule();

	virtual void Integrate(float delta);
	void SetMasse(float masse);
	float InverseMasse();
	virtual void Draw(RenderWindow* window);
	float GetMasse() { return masse; };
	void clearForceAcc();
	void addForce(const Vector3D& force);
};

