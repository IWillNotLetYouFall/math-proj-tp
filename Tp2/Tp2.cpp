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
	//Regroupe les forces pour forloop l'addEntry
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
	vector<Particule*> fuseParticles;

	//TP2 Tests
	PhysicWorld physicW = PhysicWorld(2);
	bool peutSplit = true;
	bool peutFuse = true;

	//Particule Corps du blob
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

	//Ajout de la gravité
	bodyParts.push_back(new BodyPart(new ParticleGravity(Vector3D(0, -200.f)), &head)); //Body
	bodyParts.push_back(new BodyPart(new ParticleGravity(Vector3D(200, 200.f)), &legR)); //Right Leg (side-gravity)
	bodyParts.push_back(new BodyPart(new ParticleGravity(Vector3D(-200, 200.f)), &legL)); //Left Leg (side-gravity)
	bodyParts.push_back(new BodyPart(new ParticleGravity(Vector3D(200, -15.f)), &armR)); //Right Arm (side-gravity)
	bodyParts.push_back(new BodyPart(new ParticleGravity(Vector3D(-200, -15.f)), &armL)); //Left Arm (side-gravity)

	//Springs
	bodyParts.push_back(new BodyPart(new SpringParticles(&body, 5.f, -10.f), &armL)); //Left Arm (Particles Spring)
	bodyParts.push_back(new BodyPart(new SpringParticles(&body, 5.f, -10.f), &armR)); //Right Arm (Particles Spring)
	bodyParts.push_back(new BodyPart(new SpringBungee(&body, 10.f, 20.f), &legL)); //Left Leg (Particles Bungee)
	bodyParts.push_back(new BodyPart(new SpringBungee(&body, 10.f, 20.f), &legR)); //Right Leg (Particles Bungee)

	//Body suit la souris
	bodyParts.push_back(new BodyPart(new SpringParticles(&reticle, 40.4f, 1), &body)); //Corps suit souris (Particles Spring)

	//Spring Fixed
	Particule fixedPart = Particule(Color::Yellow, 30);
	fixedPart.position = Vector3D(300.0f, 200.0f);
	Vector3D sFixedPos = fixedPart.position + Vector3D(0, -80.0f);
	bodyParts.push_back(new BodyPart(new ParticleGravity(Vector3D(0, -100.f)), &fixedPart)); //Gravite
	bodyParts.push_back(new BodyPart(new SpringFixed(sFixedPos, 3.f, 100.f), &fixedPart)); //Fixed Particles (Fixed Spring)
	physicW.AddParticle(&fixedPart);
	fuseParticles.push_back(&fixedPart);

	//Rod Collision
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

	RenderWindow window(VideoMode(800, 600), "TP2", Style::Default);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	//Vectors
	Vector2f mousePosWindow;



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
		//Split Blob jaune
		if (Keyboard::isKeyPressed(Keyboard::O))
		{
			Particule* lastPart = fuseParticles[fuseParticles.size() - 1];
			float lastRadius = lastPart->GetRadius();

			//Ne pas split lorsque dimensions trop petites
			if (lastRadius > 1 && peutSplit) {
				Particule* newBlob = new Particule(Color::Yellow, lastRadius / 2);
				newBlob->position = Vector3D(lastPart->position);
				newBlob->test = true;

				Vector3D sFixedPos = newBlob->position;
				ParticleGravity* partiGravity = new ParticleGravity(Vector3D(0, 300.f)); //Gravite
				SpringBungee* partiSpring = new SpringBungee(lastPart, 10.f, 5.f); //Fixed Particles (Fixed Spring)
				physicW.AddEntry(newBlob, partiGravity);
				physicW.AddEntry(newBlob, partiSpring);
				physicW.AddParticle(newBlob);
				fuseParticles.push_back(newBlob);

				lastPart->SetRadius(lastRadius / 2);

				peutSplit = false;
			}
		}
		else
			peutSplit = true;

		//Fuse Blob Jaunes
		if (Keyboard::isKeyPressed(Keyboard::P) && fuseParticles.size() > 1)
		{
			Particule* lastPart = fuseParticles[fuseParticles.size() - 1];
			Particule* prevPart = fuseParticles[fuseParticles.size() - 2];
			float lastRadius = lastPart->GetRadius();

			if (peutFuse) {
				physicW.RemoveParticle(lastPart);
				physicW.RemoveEntries(lastPart);
				fuseParticles.erase(fuseParticles.end() - 1);

				prevPart->SetRadius(lastPart->GetRadius() * 2);

				peutFuse = false;
			}
		}
		else
			peutFuse = true;


		mousePosWindow = Vector2f(Mouse::getPosition(window));

		reticle.position = Vector3D(mousePosWindow.x, mousePosWindow.y);
		reticle.Integrate(0);
		reticleIn.setPosition(mousePosWindow);

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

		//Draw Lignes Fusion
		if (fuseParticles.size() >= 2) {
			//fuseParticles[1]->shape.setPosition(100, 100);
			float a = 0.1f;
		}

		for (Particule* part : fuseParticles) {
			window.draw(part->shape);
		}
		

		window.draw(reticle.shape);
		window.draw(reticleIn);

		window.display();

		deltaTime = deltaClock.restart();
	}

	std::cout << "Finised Game!\n";

	return 0;
}