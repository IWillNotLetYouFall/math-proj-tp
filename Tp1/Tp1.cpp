// Test1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include "Vector3D.h"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <math.h>
#include <vector>
#include <cstdlib>
#include "TestChild1.h"
#include "Character.h"
#include "PhysicWorld.h"
#include "SpringParticles.h"
#include "ParticleCable.h"

using namespace sf;

int main()
{
	PhysicWorld physicW = PhysicWorld(2);

	Particule body = Particule();
	body.shape->setScale(5.f,5.f);
	body.shape->setFillColor(Color::Blue);
	body.shape->setPosition(100.0f, 100.0f);
	body.shape->setOrigin(5.f, 5.f);
	//body.position = Vector3D(10.0f,10.0f,10.0f);
	Particule head = Particule();
	head.shape->setScale(3.f, 3.f);
	head.shape->setFillColor(Color::White);
	head.shape->setPosition(100.0f, 50.0f);
	head.shape->setOrigin(3.f, 3.f);
	Particule lArm = Particule();
	lArm.shape->setScale(2.f, 2.f);
	lArm.shape->setFillColor(Color::Cyan);
	lArm.shape->setPosition(60.0f, 70.0f);
	lArm.shape->setOrigin(2.f, 2.f);
	Particule rArm = Particule();
	rArm.shape->setScale(2.f, 2.f);
	rArm.shape->setFillColor(Color::Cyan);
	rArm.shape->setPosition(140.0f, 70.0f);
	rArm.shape->setOrigin(2.f, 2.f);
	Particule lLeg = Particule();
	lLeg.shape->setScale(2.f, 2.f);
	lLeg.shape->setFillColor(Color::Cyan);
	lLeg.shape->setPosition(60.0f, 130.0f);
	lLeg.shape->setOrigin(2.f, 2.f);
	Particule rLeg = Particule();
	rLeg.shape->setScale(2.f, 2.f);
	rLeg.shape->setFillColor(Color::Cyan);
	rLeg.shape->setPosition(140.0f, 130.0f);
	rLeg.shape->setOrigin(2.f, 2.f);


	SpringParticles HEAD = SpringParticles(&head,5.f,10.f);
	SpringParticles LARM = SpringParticles(&lArm,5.f,10.f);
	SpringParticles RARM = SpringParticles(&rArm,5.f,10.f);
	SpringParticles LLEG = SpringParticles(&lLeg,5.f,10.f);
	SpringParticles RLEG = SpringParticles(&rLeg,5.f,10.f);

	ParticleCable cableHead = ParticleCable();
	cableHead.setParticle1(&body);
	cableHead.setParticle2(&head);
	ParticleCable cableLarm = ParticleCable();
	cableLarm.setParticle1(&body);
	cableLarm.setParticle2(&lArm);
	ParticleCable cableRarm = ParticleCable();
	cableRarm.setParticle1(&body);
	cableRarm.setParticle2(&lArm);
	ParticleCable cableLleg = ParticleCable();
	cableLleg.setParticle1(&body);
	cableLleg.setParticle2(&lArm);
	ParticleCable cableRleg = ParticleCable();
	cableRleg.setParticle1(&body);
	cableRleg.setParticle2(&lArm);

	physicW.AddEntry(&body, &HEAD, &cableHead);
	physicW.AddEntry(&body, &LARM, &cableLarm);
	physicW.AddEntry(&body, &RARM, &cableRarm);
	physicW.AddEntry(&body, &LLEG, &cableLleg);
	physicW.AddEntry(&body, &RLEG, &cableRleg);



	Physics::NewInstance();
	//Tests
	TestParent testParent = TestParent(5);
	testParent.PrintMess();
	TestChild1 testChild = TestChild1(4);
	testChild.PrintMess();


	srand(time(NULL));

	RenderWindow window(VideoMode(1600, 900), "TP1", Style::Default);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	//player
	Character player = Character(Color::White, Vector3D(100, window.getSize().y - 25.f), 25.f, window);

	//Reticle
	CircleShape reticle(10.f);
	reticle.setFillColor(Color::Red);
	reticle.setPointCount(30);
	reticle.setOrigin(10.f, 10.f);
	CircleShape reticleIn(4.f);
	reticleIn.setFillColor(Color::White);
	reticleIn.setPointCount(30);
	reticleIn.setOrigin(4.f, 4.f);

	//Enemy
	RectangleShape enemy = RectangleShape(Vector2f(50.f, 50.f));
	//enemy.setFillColor(Color::Magenta);
	//enemy.setSize(Vector2f(50.f, 50.f));
	int spawnCounter = 20;

	//Wall
	RectangleShape wall;
	wall.setFillColor(Color::Green);
	wall.setSize(Vector2f(50.f, 150.f));
	wall.setPosition(300, window.getSize().y - 150.f);

	std::vector<RectangleShape> enemies;

	//Vectors
	Vector2f turretCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;


	Clock deltaClock;
	Time deltaTime = deltaClock.restart();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		physicW.StartFrame();
		//Update
		//Vectors
		mousePosWindow = Vector2f(Mouse::getPosition(window));
		reticle.setPosition(mousePosWindow);
		reticleIn.setPosition(mousePosWindow);

		player.Update(wall, deltaTime.asSeconds());


		//Enemies
		if (spawnCounter < 20)
			spawnCounter++;

		if (spawnCounter >= 20 && enemies.size() < 3)
		{
			enemy.setPosition(Vector2f(rand() % window.getSize().x, rand() % (window.getSize().y - 100)));
			enemies.push_back(RectangleShape(enemy));

			spawnCounter = 0;
		}

		physicW.RunPhysics(deltaTime.asSeconds());
		//Draw
		window.clear();

		for (size_t i = 0; i < enemies.size(); i++)
			window.draw(enemies[i]);

		window.draw(wall);
		window.draw(reticle);
		window.draw(reticleIn);
		window.draw(*body.shape);
		window.draw(*head.shape);
		window.draw(*lArm.shape);
		window.draw(*rArm.shape);
		window.draw(*lLeg.shape);
		window.draw(*rLeg.shape);

		player.Draw();

		window.display();

		deltaTime = deltaClock.restart();
	}

	std::cout << "Finised Game!\n";

	return 0;
}