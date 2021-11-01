<<<<<<< HEAD:Tp1/Particule.h
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

	int masseMax = 1000;
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

=======
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

>>>>>>> GettingRevert:Tp2/Particule.h
