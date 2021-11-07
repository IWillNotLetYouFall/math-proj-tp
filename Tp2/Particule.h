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
	int masseMax = 10000000;
	Vector3D forceAcc;
	float maxSpeed = 320.f;

public:
	CircleShape shape;
	Vector3D position;
	Vector3D velocite;
	//Vector3D acceleration = 0;
	float inverseMasse = 0;
	float damping = 0.2f;
	bool test = false;

public:
	Particule();
	Particule(Color color, float radius);
	~Particule();
	void Integrate(float delta);
	void SetMaxSpeed(float speed);
	void SetMasse(float masse);
	float InverseMasse();
	float GetMasse() { return masse; };
	void clearForceAcc();
	void addForce(const Vector3D& force);
	float GetRadius();
	void SetRadius(float radius);
	Vector3D getAcceleration() { return forceAcc; };
};

