#pragma once
#include "Vector3D.h"
#include <cmath>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>

using namespace sf;

class Particule
{
private:
	float masse = 1;
	Vector3D velInitiale = Vector3D(1, 1, 0);
	float damping = 0.995f;

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
};

