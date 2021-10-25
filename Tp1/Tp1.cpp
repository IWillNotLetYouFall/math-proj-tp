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

using namespace sf;

int main()
{
	PhysicWorld physicW;



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

		//Draw
		window.clear();

		for (size_t i = 0; i < enemies.size(); i++)
			window.draw(enemies[i]);

		window.draw(wall);
		window.draw(reticle);
		window.draw(reticleIn);

		player.Draw();

		window.display();

		deltaTime = deltaClock.restart();
	}

	std::cout << "Finised Game!\n";

	return 0;
}