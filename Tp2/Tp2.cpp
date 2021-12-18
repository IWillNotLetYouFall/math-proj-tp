// Test1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include "Vector3D.h"
#include "Particule.h"
#include "Laser.h"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <math.h>
#include <vector>
#include <cstdlib>
#include "PhysicWorld.h"
#include "SpringParticles.h"
#include "ParticleRod.h"
#include "ParticleGravity.h"
#include "SpringBungee.h"
#include "SpringFixed.h"
#include "SpringParticles.h"
#include "RigidBody.h"
#include "GravityForceGeneratorBody.h"
#include "SpringForceGenerator.h"
#include "Box.h"
#include "Plane.h"

using namespace sf;

int main()
{
	//Regroupe les forces pour forloop l'addEntry
	class BodyPart {
	public:
		BodyPart(ForceGeneratorBody* forceGen, RigidBody* particule) {
			this->forceGen = forceGen;
			this->particule = particule;
		}
		ForceGeneratorBody* forceGen;
		RigidBody* particule;
	};

	//TP2 Tests
	PhysicWorld physicW = PhysicWorld(2);
	bool peutSplit = true;
	bool peutFuse = true;

	//TP4 Tests
	bool pushed = false;
	bool touch = false;

	RigidBody ball = RigidBody(Color::Yellow, 90);
	ball.SetPosition(Vector3D(100.0f, 500.0f));
	ball.setMass(.2);
	ball.SetMaxSpeed(3000);

	Box box;
	//THIS IS THE BOX THROWN IN THE ROOM
	box.body = &ball;
	box.offset = Matrix4();
	box.halfsize = Vector3D(45, 45, 60);
	box.BoundingSphere.radius = 49;

	physicW.AddRigidBody(box.body);
	physicW.addCoordinates(600,600,600);

	Vector3D origin = (300, 300, 0);
	//Room walls
	Plane WallLeft;
	WallLeft.body = new RigidBody(1000000); //infinitemass
	WallLeft.body->isAwake = false;
	WallLeft.body->SetPosition(Vector3D(0, 300, 0));
	WallLeft.body->setRotation(-90, 0, 0);
	WallLeft.normal = WallLeft.body->getRotation().Normalize();
	Plane WallRight;
	WallRight.body = new RigidBody(1000000); //infinitemass
	WallRight.body->isAwake = false;
	WallRight.body->SetPosition(Vector3D(600, 300, 0));
	WallRight.body->setRotation(90, 0, 0);
	WallRight.normal = WallRight.body->getRotation().Normalize();
	Plane WallUp;
	WallUp.body = new RigidBody(1000000); //infinitemass
	WallUp.body->isAwake = false;
	WallUp.body->SetPosition(Vector3D(300, 0, 0));
	WallUp.body->setRotation(0, 0, 180);
	WallUp.normal = WallUp.body->getRotation().Normalize();
	Plane WallDown;
	WallDown.body = new RigidBody(1000000); //infinitemass
	WallDown.body->isAwake = false;
	WallDown.body->SetPosition(Vector3D(300, 600, 0));
	WallDown.body->setRotation(0, 0, 0);
	WallDown.normal = WallDown.body->getRotation().Normalize();
	Plane WallFront;
	WallFront.body = new RigidBody(1000000); //infinitemass
	WallFront.body->isAwake = false;
	WallFront.body->SetPosition(Vector3D(300, 300, -300));
	WallFront.body->setRotation(0, 0, -90);
	WallFront.normal = WallFront.body->getRotation().Normalize();
	Plane WallBack;
	WallBack.body = new RigidBody(1000000); //infinitemass
	WallBack.body->isAwake = false;
	WallBack.body->SetPosition(Vector3D(300, 300, 300));
	WallBack.body->setRotation(0, 0, 90);
	WallBack.normal = WallBack.body->getRotation().Normalize();


	//TP1 Part
	srand(time(NULL));

	RenderWindow window(VideoMode(800, 600), "TP4", Style::Default);
	window.setFramerateLimit(60);

	//Vectors
	Vector2f mousePosWindow;


	Clock deltaClock;
	Time deltaTime = deltaClock.restart();
	while (window.isOpen() and !touch)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		physicW.StartFrame();


		if (Keyboard::isKeyPressed(Keyboard::P)) {
			if (!pushed)
			{
				box.body->AddForceAtBodyPoint(Vector3D(50, -180, -8), Vector3D(0, -20.f, 0));
				//ball.AddForceAtBodyPoint(Vector3D(50, -180, -10), Vector3D(0, -20.f, 0)); //touch front
				physicW.AddEntry(box.body, new GravityForceGeneratorBody(Vector3D(0, 10.f)));
				pushed = true;
			}
		}

		//if (box.body->GetPosition().y - 49 <= 0) //touches top
		//{
		//	cout << "top" << endl;
		//	touch = true;
		//}
		//else if (box.body->GetPosition().y + 49 >= 600) //touches bottom
		//{
		//	cout << "bottom" << endl;
		//	touch = true;
		//}
		//else if (box.body->GetPosition().x - 49 <= 0) //touches left
		//{
		//	cout << "left" << endl;
		//	touch = true;
		//}
		//else if (box.body->GetPosition().x + 49 >= 600) //touches right
		//{
		//	cout << "right" << endl;
		//	touch = true;
		//}
		//else if (box.body->GetPosition().z - 49 <= -300) //touches front
		//{
		//	cout << "front" << endl;
		//	touch = true;
		//}
		//else if (box.body->GetPosition().z + 49 >= 300) //touches back
		//{
		//	cout << "back" << endl;
		//	touch = true;
		//}

		if (touch) break;

		physicW.RunPhysics(deltaTime.asSeconds());

		//Draw
		window.clear();

		window.draw(box.body->shape);

		window.display();

		deltaTime = deltaClock.restart();
	}

	std::cout << "Finised Game!\n";

	return 0;
}