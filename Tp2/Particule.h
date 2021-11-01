#pragma once
#include "Vector3D.h"
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>

using namespace sf;

class Particule
{
private:
	float masse = 1;
	Vector3D velInitiale = Vector3D(1, 1, 0);
	int masseMax = 1000;
	Vector3D forceAcc;

public:
	CircleShape shape;
	Vector3D position;
	Vector3D velocite;
	//Vector3D acceleration = 0;
	float maxSpeed = 600.f;
	float inverseMasse = 0;
	float damping = 1;

public:
	Particule();
	Particule(const Particule& base);
	~Particule();
	void Integrate(float delta);
	void SetMasse(float masse);
	float InverseMasse();
	float GetMasse() { return masse; };
	void clearForceAcc();
	void addForce(const Vector3D& force);
	Vector3D getAcceleration() { return forceAcc; };
};

