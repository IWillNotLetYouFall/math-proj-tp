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

using namespace sf;

int main()
{
	class BodyPart {
	public:
		BodyPart(ParticleForceGenerator* forceGen, Particule* particule) {
			this->forceGen = forceGen;
			this->particule = particule;
		}
		ParticleForceGenerator* forceGen;
		Particule* particule;
	};
	vector<BodyPart*> bodyParts;

	//TP2 Tests
	PhysicWorld physicW = PhysicWorld(2);

	Particule body = Particule(Color::Blue, 25);
	body.position = Vector3D(100.0f, 100.0f);
	body.SetMasse(50);
	body.SetMaxSpeed(3000);
	body.damping = 0.01f;
	physicW.AddParticle(&body);

	//Reticules qui suit la souris
	Particule reticle = Particule(Color::Red, 10);
	body.SetMasse(500000);
	CircleShape reticleIn(4.f);
	reticleIn.setFillColor(Color::White);
	reticleIn.setPointCount(30);
	reticleIn.setOrigin(4.f, 4.f);

	//Particules du blob
	Particule head = Particule(Color::White, 18);
	head.position = Vector3D(100.0f, 80.0f);
	physicW.AddParticle(&head);
	Particule legR = Particule(Color::White, 16);
	legR.position = Vector3D(110.0f, 120.0f);
	physicW.AddParticle(&legR);
	Particule legL = Particule(Color::White, 16);
	legL.position = Vector3D(90.0f, 120.0f);
	physicW.AddParticle(&legL);
	Particule armR = Particule(Color::Red, 15);
	armR.position = Vector3D(120.0f, 100.0f);
	physicW.AddParticle(&armR);
	Particule armL = Particule(Color::Red, 15);
	armL.position = Vector3D(80.0f, 100.0f);
	physicW.AddParticle(&armL);

	//forceGens.push_back();
	bodyParts.push_back(new BodyPart(new ParticleGravity(Vector3D(0, 0.f)), &body)); //Body
	bodyParts.push_back(new BodyPart(new ParticleGravity(Vector3D(0, -200.f)), &head)); //Body
	bodyParts.push_back(new BodyPart(new ParticleGravity(Vector3D(200, 200.f)), &legR)); //Right Leg (side-gravity)
	bodyParts.push_back(new BodyPart(new ParticleGravity(Vector3D(-200, 200.f)), &legL)); //Left Leg (side-gravity)
	bodyParts.push_back(new BodyPart(new ParticleGravity(Vector3D(200, -15.f)), &armR)); //Right Arm (side-gravity)
	bodyParts.push_back(new BodyPart(new ParticleGravity(Vector3D(-200, -15.f)), &armL)); //Left Arm (side-gravity)

	//Springs
	bodyParts.push_back(new BodyPart(new SpringParticles(&body, 5.f, -10.f), &armL)); //Left Leg (Particles Spring)
	bodyParts.push_back(new BodyPart(new SpringParticles(&body, 5.f, -10.f), &armR)); //Right Leg (Particles Spring)
	bodyParts.push_back(new BodyPart(new SpringBungee(&body, 10.f, 20.f), &legL)); //Left Leg (Particles Spring)
	bodyParts.push_back(new BodyPart(new SpringBungee(&body, 10.f, 20.f), &legR)); //Right Leg (Particles Spring)

	//Body suit la souris
	bodyParts.push_back(new BodyPart(new SpringParticles(&reticle, 40.4f, 1), &body)); //Left Leg (Particles Spring)


	//Particles
	//ParticleForceGenerator* LEGSPRING = new SpringParticles(&body, 3.f, 100.f);
	//Fixed
	//ParticleForceGenerator* LEGSPRING = new SpringFixed(body.position, 3.f, 100.f);
	//Bungee
	//ParticleForceGenerator* LEGSPRING = new SpringBungee(&body, 3.f, 100.f);

	//Cable Collision
	ParticleRod* cableHead = new ParticleRod(35);
	cableHead->setParticle1(&head);
	cableHead->setParticle2(&body);
	physicW.AddContactGenerator(cableHead);

	//Cable Collision
	ParticleCable* cableArmL = new ParticleCable(55, 0.6f);
	cableArmL->setParticle1(&armL);
	cableArmL->setParticle2(&body);
	physicW.AddContactGenerator(cableArmL);
	
	ParticleCable* cableArmR = new ParticleCable(55, 0.6f);
	cableArmR->setParticle1(&armR);
	cableArmR->setParticle2(&body);
	physicW.AddContactGenerator(cableArmR);
	
	ParticleCable* cableLegL = new ParticleCable(65, 0.6f);
	cableLegL->setParticle1(&legL);
	cableLegL->setParticle2(&body);
	physicW.AddContactGenerator(cableLegL);
	
	ParticleCable* cableLegR = new ParticleCable(65, 0.3f);
	cableLegR->setParticle1(&legR);
	cableLegR->setParticle2(&body);
	physicW.AddContactGenerator(cableLegR);

	//Ajout des forces dans le gestionnaire de physiques
	for (BodyPart* part : bodyParts)
		physicW.AddEntry(part->particule, part->forceGen);


	//TP1 Part
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

		reticle.position = Vector3D(mousePosWindow.x, mousePosWindow.y);
		reticle.Integrate(0);
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

		physicW.RunPhysics(deltaTime.asSeconds());

		//Draw
		window.clear();

		//TP2
		//for (BodyPart* part : bodyParts)
			//window.draw(part->particule->shape);
		window.draw(body.shape);
		window.draw(head.shape);
		window.draw(armL.shape);
		window.draw(armR.shape);
		window.draw(legL.shape);
		window.draw(legR.shape);

		window.draw(reticle.shape);
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