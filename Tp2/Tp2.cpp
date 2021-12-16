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
	//bodyParts.push_back(new BodyPart(new GravityForceGeneratorBody(Vector3D(0, 100.f)), &ball)); //Left Arm (side-gravity)
	//ball.AddForceAtBodyPoint(Vector3D(6000, 0, 0), Vector3D(0, 100, 0));
	physicW.AddRigidBody(&ball);


	//TP1 Part
	srand(time(NULL));

	RenderWindow window(VideoMode(800, 600), "TP4", Style::Default);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

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
				ball.AddForceAtBodyPoint(Vector3D(50, -180, -8), Vector3D(0, -20.f, 0));
				//ball.AddForceAtBodyPoint(Vector3D(50, -180, -10), Vector3D(0, -20.f, 0)); //touch front
				physicW.AddEntry(&ball, new GravityForceGeneratorBody(Vector3D(0, 10.f)));
				pushed = true;
			}
		}

		if (ball.GetPosition().y - 77.5 <= 0) //touches top
		{
			cout << "top" << endl;
			touch = true;
		}
		else if (ball.GetPosition().y + 77.5 >= 600) //touches bottom
		{
			cout << "bottom" << endl;
			touch = true;
		}
		else if (ball.GetPosition().x - 77.5 <= 0) //touches left
		{
			cout << "left" << endl;
			touch = true;
		}
		else if (ball.GetPosition().x + 77.5 >= 800) //touches right
		{
			cout << "right" << endl;
			touch = true;
		}
		else if (ball.GetPosition().z <= -80) //touches front
		{
			cout << "front" << endl;
			touch = true;
		}
		else if (ball.GetPosition().z >= 80) //touches back
		{
			cout << "back" << endl;
			touch = true;
		}

		if (touch) break;

		physicW.RunPhysics(deltaTime.asSeconds());

		//Draw
		window.clear();

		window.draw(ball.shape);


		window.display();

		deltaTime = deltaClock.restart();
	}

	std::cout << "Finised Game!\n";

	return 0;
}