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
#include "CollisionData.h"
#include "CollisionDetector.h"

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

	//TP4 Tests (Gab)
	CollisionData colData;

	Vector3D boxSize = Vector3D(90, 90, 90);
	RigidBody ball = RigidBody(Color::Yellow, boxSize);
	ball.SetPosition(Vector3D(100.0f, 500.0f));
	ball.setMass(.2);
	ball.SetMaxSpeed(3000);

	Box box;
	//THIS IS THE BOX THROWN IN THE ROOM
	box.body = &ball;
	box.offset = Matrix4();
	box.halfsize = Vector3D(boxSize.x/2, boxSize.y / 2, boxSize.z / 2);
	//box.BoundingSphere.radius = 49;

	physicW.AddRigidBody(box.body);

	//Other boxes
	Vector3D boxesSizes = Vector3D(24, 24, 24);
	RigidBody balls1 = RigidBody(Color::Red, boxesSizes);
	balls1.setMass(.2);
	balls1.SetMaxSpeed(3000);
	Box boxes1;
	boxes1.offset = Matrix4();
	boxes1.halfsize = Vector3D(boxesSizes.x / 4, boxesSizes.y / 4, boxesSizes.z / 4);
	boxes1.body = &balls1;
	boxes1.body->SetPosition(Vector3D(40, 200));

	RigidBody balls2 = RigidBody(Color::Red, boxesSizes);
	balls2.setMass(.2);
	balls2.SetMaxSpeed(3000);
	Box boxes2;
	boxes2.offset = Matrix4();
	boxes2.halfsize = Vector3D(boxesSizes.x / 4, boxesSizes.y / 4, boxesSizes.z / 4);
	boxes2.body = &balls2;
	boxes2.body->SetPosition(Vector3D(100, 20));

	RigidBody balls3 = RigidBody(Color::Red, boxesSizes);
	balls3.setMass(.2);
	balls3.SetMaxSpeed(3000);
	Box boxes3;
	boxes3.offset = Matrix4();
	boxes3.halfsize = Vector3D(boxesSizes.x / 3, boxesSizes.y / 3, boxesSizes.z / 3);
	boxes3.body = &balls3;
	boxes3.body->SetPosition(Vector3D(200,100));

	RigidBody balls4 = RigidBody(Color::Red, boxesSizes);
	balls4.setMass(.2);
	balls4.SetMaxSpeed(3000);
	Box boxes4;
	boxes4.offset = Matrix4();
	boxes4.halfsize = Vector3D(boxesSizes.x / 3, boxesSizes.y / 3, boxesSizes.z / 3);
	boxes4.body = &balls4;
	boxes4.body->SetPosition(Vector3D(700, 150));

	physicW.AddRigidBody(boxes1.body);
	physicW.AddRigidBody(boxes2.body);
	physicW.AddRigidBody(boxes3.body);
	physicW.AddRigidBody(boxes4.body);

	Vector3D origin = (400, 300, 0);
	//Room walls
	Plane WallLeft;
	WallLeft.body = new RigidBody(Color::Green, Vector3D(2, 600, 1)); //infinitemass
	WallLeft.body->isAwake = false;
	WallLeft.body->SetPosition(Vector3D(0, 300, 0));
	WallLeft.normal = Vector3D(1, 0, 0);
	WallLeft.offset = 0;
	physicW.AddRigidBody(WallLeft.body);


	Plane WallRight;
	WallRight.body = new RigidBody(Color::Green, Vector3D(2, 600, 1)); //infinitemass
	WallRight.body->isAwake = false;
	WallRight.body->SetPosition(Vector3D(800, 300, 0));
	WallRight.normal = Vector3D(-1, 0, 0);
	WallRight.offset = -800;
	physicW.AddRigidBody(WallRight.body);

	Plane WallUp;
	WallUp.body = new RigidBody(Color::Green, Vector3D(800, 3, 1)); //infinitemass
	WallUp.body->isAwake = false;
	WallUp.body->SetPosition(Vector3D(400, 0, 0));
	WallUp.normal = Vector3D(0, 1, 0);
	WallUp.offset = 0;
	physicW.AddRigidBody(WallUp.body);

	Plane WallDown;
	WallDown.body = new RigidBody(Color::Green, Vector3D(800, 2, 1)); //infinitemass
	WallDown.body->isAwake = false;
	WallDown.body->SetPosition(Vector3D(400, 600, 0));
	WallDown.normal = Vector3D(0,-1,0);
	WallDown.offset = -600;
	physicW.AddRigidBody(WallDown.body);

	Plane WallFront;
	WallFront.body = new RigidBody(1000000); //infinitemass
	WallFront.body->isAwake = false;
	WallFront.body->SetPosition(Vector3D(400, 300, -300));
	WallFront.normal = Vector3D(0, 0, -1);
	WallFront.offset = -300;
	physicW.AddRigidBody(WallFront.body);

	Plane WallBack;
	WallBack.body = new RigidBody(1000000); //infinitemass
	WallBack.body->isAwake = false;
	WallBack.body->SetPosition(Vector3D(400, 300, 300));
	WallBack.normal = Vector3D(0, 0, 1);
	WallBack.offset = -300;
	physicW.AddRigidBody(WallBack.body);


	//TP1 Part
	srand(time(NULL));

	RenderWindow window(VideoMode(800, 600), "TP4", Style::Default);
	window.setFramerateLimit(60);

	//Vectors
	Vector2f mousePosWindow;


	Clock deltaClock;
	Time deltaTime = deltaClock.restart();
	while (window.isOpen())
	{
		if (touch) {
			deltaTime = deltaClock.restart();
			continue;
		}

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
				box.body->AddForceAtBodyPoint(Vector3D(50, -180, 8), Vector3D(0, -20.f, 0));
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
		//else if (box.body->GetPosition().x + 49 >= 800) //touches right
		//{
		//	cout << "right" << endl;
		//	touch = true;
		//}
		//else if (box.body->GetPosition().z - 49 <= (-80 - 49)) //touches front
		//{
		//	cout << "front" << endl;
		//	touch = true;
		//}
		//else if (box.body->GetPosition().z + 49 >= (80 + 49)) //touches back
		//{
		//	cout << "back" << endl;
		//	touch = true;
		//}

		if (touch) break;

		physicW.RunPhysics(deltaTime.asSeconds());

		//Draw
		window.clear();

		window.draw(box.body->shape);
		window.draw(WallUp.body->shape);
		window.draw(WallDown.body->shape);
		window.draw(WallLeft.body->shape);
		window.draw(WallRight.body->shape);
		window.draw(boxes1.body->shape);
		window.draw(boxes2.body->shape);
		window.draw(boxes3.body->shape);
		window.draw(boxes4.body->shape);

		window.display();

		deltaTime = deltaClock.restart();

		//TP4 Tests Gab - Narrow
		colData.Reset();
		if (CollisionDetector::BoxPlaneDetect(box, WallUp, &colData) != 0)
			touch = true;
		if (CollisionDetector::BoxPlaneDetect(box, WallDown, &colData) != 0)
			touch = true;
		if (CollisionDetector::BoxPlaneDetect(box, WallLeft, &colData) != 0)
			touch = true;
		if (CollisionDetector::BoxPlaneDetect(box, WallRight, &colData) != 0)
			touch = true;
		if (CollisionDetector::BoxPlaneDetect(box, WallFront, &colData) != 0)
			touch = true;
		if (CollisionDetector::BoxPlaneDetect(box, WallBack, &colData) != 0)
			touch = true;
		if (touch) 
			continue;
	}

	std::cout << "Finised Game!\n";

	return 0;
}