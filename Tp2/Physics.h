#pragma once
#include "Vector3D.h"
#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "OldContact.h"

using namespace sf;
using namespace std;

class Physics
{
public:
	static Physics* instance;
	vector<OldContact*> contacts;
	vector<CircleShape*> circles; //Devient Particule
	vector<RectangleShape*> rectangles; //Devient Mur Fixe

public:
	static void NewInstance();
	static Physics* GetInstance();
	void AddCircle(CircleShape* circle);
	void RemoveCircle(CircleShape* circle);
	void AddRectangle(RectangleShape* rectangle);
	void RemoveRectangle(RectangleShape* rectangle);
	void RemoveContact(OldContact* contact);
	OldContact* CollisionDetection(Shape* shape, float weight, Vector3D vel, float delta); //Check si déja collision, ensuite, check si vel fait collision(post-pre)
	Physics(void) {}

private:
	OldContact* GetCollidedContact(Shape* shape);
	OldContact* ContactBetweenCircles(Vector3D vel, float weight, CircleShape* shape); //null si aucun point de contact
};

