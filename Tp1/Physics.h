#pragma once
#include "Vector3D.h"
#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "Contact.h"

using namespace sf;
using namespace std;

class Physics
{
public:
	static Physics* instance;
	vector<Contact*> contacts;
	vector<CircleShape*> circles; //Devient Particule
	vector<RectangleShape*> rectangles; //Devient Mur Fixe

public:
	static void NewInstance();
	static Physics* GetInstance();
	void AddCircle(CircleShape* circle);
	void RemoveCircle(CircleShape* circle);
	void AddRectangle(RectangleShape* rectangle);
	void RemoveRectangle(RectangleShape* rectangle);
	void RemoveContact(Contact* contact);
	Contact* CollisionDetection(Shape* shape, float weight, Vector3D vel, float delta); //Check si d?ja collision, ensuite, check si vel fait collision(post-pre)
	Physics(void) {}

private:
	Contact* GetCollidedContact(Shape* shape);
	Contact* ContactBetweenCircles(Vector3D vel, float weight, CircleShape* shape); //null si aucun point de contact
};

