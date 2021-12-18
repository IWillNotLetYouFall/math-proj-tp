#pragma once
#include "Vector3D.h"
#include <cmath>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

using namespace sf;

class Collider {
public:
	Shape* shape;
	Vector3D velocity;
	Vector3D position;
	float weight;
public:
	Collider(Shape* shape, Vector3D position, Vector3D vel, float weight) {
		this->shape = shape;
		this->position = position;
		this->velocity = vel;
		this->weight = weight;
	}
};
class OldContact
{
public:
	Collider* collider; //Check les collided avant col check pour vérifier s'il y a eu coll le tour d'avant. Après collided check, remove Contact Point.
	Collider* collided;
	Vector3D contactPos;

public:
	OldContact(Collider* collider, Collider* collided, Vector3D contactPos);
};

