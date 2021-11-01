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
#include "ParticleGravity.h"
#include "SpringBungee.h"

using namespace sf;

int main()
{
	//TP2 Tests
	PhysicWorld physicW = PhysicWorld(2);

	Particule body = Particule();
	body.shape.setScale(5.f, 5.f);
	body.shape.setFillColor(Color::Blue);
	body.shape.setOrigin(5.f, 5.f);
	body.position = Vector3D(100.0f, 100.0f);

	Particule leg = Particule();
	leg.shape.setScale(5.f, 5.f);
	leg.shape.setFillColor(Color::White);
	leg.shape.setOrigin(5.f, 5.f);
	leg.position = Vector3D(100.0f, 120.0f);

	ParticleForceGenerator* BODY = new ParticleGravity(Vector3D(0, 0.f));
	ParticleForceGenerator* LEG = new ParticleGravity(Vector3D(0, 15.f));
	ParticleForceGenerator* LEGSPRING = new SpringBungee(&body, 1.1f, 100.1f);





	srand(time(NULL));

	bool grounded = true;
	bool canShoot = true;
	float vsp = 0.f;

	RenderWindow window(VideoMode(800, 600), "TP2", Style::Default);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	//player
	RectangleShape player;
	player.setFillColor(Color::White);
	player.setSize(Vector2f(50.f, 50.f));
	player.setOrigin(25.f, 25.f);
	player.setPosition(100, window.getSize().y - 25.f);

	//turret
	RectangleShape turret;
	turret.setFillColor(Color::Blue);
	turret.setSize(Vector2f(30.f, 50.f));
	turret.setOrigin(15.f, 25.f);
	turret.setPosition(100, window.getSize().y - 35.f);

	//Reticle
	CircleShape reticle(10.f);
	reticle.setFillColor(Color::Red);
	reticle.setPointCount(30);
	reticle.setOrigin(10.f, 10.f);
	CircleShape reticleIn(4.f);
	reticleIn.setFillColor(Color::White);
	reticleIn.setPointCount(30);
	reticleIn.setOrigin(4.f, 4.f);

	//Bullets
	int currentWeaponId = 1;
	Laser baseLaser = Laser();
	std::vector<Particule> bullets;

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
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//Update
		//Vectors
		turretCenter = Vector2f(turret.getPosition());
		mousePosWindow = Vector2f(Mouse::getPosition(window));
		aimDir = mousePosWindow - turretCenter;
		aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + (float)pow(aimDir.y, 2));

		float PI = 3.14159265f;
		float deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / PI;
		turret.setRotation(deg + 90);

		reticle.setPosition(mousePosWindow);
		reticleIn.setPosition(mousePosWindow);

		//Set Final Rotation of Ship
		//std::cout << deg << "\n";

		//turret
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			turret.move(-8.f, 0.f);
			player.move(-8.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			turret.move(8.f, 0.f);
			player.move(8.f, 0.f);
		}
		if (grounded)
		{
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				grounded = false;
				vsp = -15.f;
			}
		}
		else
			vsp += 0.8f;

		turret.move(0.f, vsp);
		player.move(0.f, vsp);

		if (player.getPosition().y > window.getSize().y - 25.f)
		{
			player.setPosition(player.getPosition().x, window.getSize().y - 25.f);
			turret.setPosition(turret.getPosition().x, window.getSize().y - 35.f);
			grounded = true;
			vsp = 0.f;
		}

		//Switch ammo
		if (Keyboard::isKeyPressed(Keyboard::Num1))
			currentWeaponId = 1;
		else if (Keyboard::isKeyPressed(Keyboard::Num2))
			currentWeaponId = 2;
		else if (Keyboard::isKeyPressed(Keyboard::Num3))
			currentWeaponId = 3;
		else if (Keyboard::isKeyPressed(Keyboard::Num4))
			currentWeaponId = 4;

		//Shooting
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (canShoot) {
				switch (currentWeaponId)
				{
				case 1:
					baseLaser.position = Vector3D(turretCenter.x, turretCenter.y);
					baseLaser.velocite = Vector3D(aimDirNorm.x, aimDirNorm.y) * baseLaser.maxSpeed;
					bullets.push_back(Laser(baseLaser));
					break;
				default:
					break;
				}
				canShoot = false;
			}
		}
		else if (!canShoot)
			canShoot = true;


		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].Integrate(deltaTime.asSeconds());

			//Collisions Écran
			if (bullets[i].position.x < 0 || bullets[i].position.x > window.getSize().x
				|| bullets[i].position.y < 0 || bullets[i].position.y > window.getSize().y)
			{
				bullets.erase(bullets.begin() + i);
			}
			else
			{
				//Collisions with enemies.
				/*for (size_t k = 0; k < enemies.size(); k++)
				{
					if (bullets[i].shape.getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
					{
						bullets.erase(bullets.begin() + i);
						enemies.erase(enemies.begin() + k);
						break;
					}
				}*/
			}
		}

		//TP2
		physicW.StartFrame();

		physicW.AddEntry(&body, BODY, NULL);
		physicW.AddEntry(&leg, LEG, NULL);
		physicW.AddEntry(&leg, LEGSPRING, NULL);



		//body.Integrate(deltaTime.asSeconds());
		physicW.RunPhysics(deltaTime.asSeconds());




		//Draw
		window.clear();

		//TP2
		window.draw(body.shape);
		window.draw(leg.shape);

		window.draw(reticle);
		window.draw(reticleIn);

		for (size_t i = 0; i < bullets.size(); i++)
		{

			window.draw(bullets[i].shape);
		}
		window.draw(player);
		window.draw(turret);

		window.display();

		deltaTime = deltaClock.restart();
	}

	std::cout << "Finised Game!\n";

	return 0;
}