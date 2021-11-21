// Test1.cpp : Ce fichier contient la fonction 'main'. L'ex�cution du programme commence et se termine � cet endroit.
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
	vector<BodyPart*> bodyParts;
	vector<RigidBody*> fuseParticles;

	//TP2 Tests
	PhysicWorld physicW = PhysicWorld(2);
	bool peutSplit = true;
	bool peutFuse = true;

	//TP3 Tests
	bool spacePressed = false;
	//Checks TP3
	bool hasCollided = false;

	//Particule Corps du blob
	RigidBody body = RigidBody(Color::Blue, 45);
	body.SetPosition(Vector3D(700.0f, 100.0f));
	body.setMass(5);
	body.SetMaxSpeed(3000);
	body.damping = 0.01f;
	physicW.AddRigidBody(&body);

	//Reticules qui suit la souris
	RigidBody reticle = RigidBody(Color::Red, 10);
	CircleShape reticleIn(4.f);
	reticleIn.setFillColor(Color::White);
	reticleIn.setPointCount(30);
	reticleIn.setOrigin(4.f, 4.f);

	//Particules du blob
	/*RigidBody head = RigidBody(Color::White, 36);
	head.SetPosition(Vector3D(100.0f, 80.0f));
	physicW.AddRigidBody(&head);
	RigidBody legR = RigidBody(Color::White, 32);
	legR.SetPosition(Vector3D(110.0f, 120.0f));
	physicW.AddRigidBody(&legR);
	RigidBody legL = RigidBody(Color::White, 32);
	legL.SetPosition(Vector3D(90.0f, 120.0f));
	physicW.AddRigidBody(&legL);
	RigidBody armR = RigidBody(Color::Red, 30);
	armR.SetPosition(Vector3D(120.0f, 100.0f));
	physicW.AddRigidBody(&armR);*/
	RigidBody armL = RigidBody(Color::Red, 30);
	armL.SetPosition(Vector3D(680.0f, 100.0f));
	//armL.setInertiaTensor(Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1));
	physicW.AddRigidBody(&armL);


	RigidBody car1 = RigidBody(Color::Cyan, 45);
	car1.SetPosition(Vector3D(600.0f, 500.0f));
	car1.setMass(5);
	car1.SetMaxSpeed(3000);
	car1.damping = 0.01f;
	physicW.AddRigidBody(&car1);

	RigidBody car2 = RigidBody(Color::Magenta, 30);
	car2.SetPosition(Vector3D(300.0f, 530.0f));
	physicW.AddRigidBody(&car2);

	//Ajout de la gravit�
	//bodyParts.push_back(new BodyPart(new GravityForceGeneratorBody(Vector3D(0, 100.f)), &body)); //Body
	//bodyParts.push_back(new BodyPart(new GravityForceGeneratorBody(Vector3D(0, -200.f)), &head)); //Body
	//bodyParts.push_back(new BodyPart(new GravityForceGeneratorBody(Vector3D(200, 200.f)), &legR)); //Right Leg (side-gravity)
	//bodyParts.push_back(new BodyPart(new GravityForceGeneratorBody(Vector3D(-200, 200.f)), &legL)); //Left Leg (side-gravity)
	//bodyParts.push_back(new BodyPart(new GravityForceGeneratorBody(Vector3D(200, -15.f)), &armR)); //Right Arm (side-gravity)
	//bodyParts.push_back(new BodyPart(new GravityForceGeneratorBody(Vector3D(0, 100.f)), &armL)); //Left Arm (side-gravity)

	//Springs
	bodyParts.push_back(new BodyPart(new SpringForceGenerator(Vector3D(0, 0), &body, Vector3D(0,0), 5.f, 10.f), &armL)); //Left Arm (Particles Spring)
	//bodyParts.push_back(new BodyPart(new SpringForceGenerator(body.GetPosition(), &armR, armR.GetPosition(), 5.f, -10.f), &armR)); //Right Arm (Particles Spring)
	//bodyParts.push_back(new BodyPart(new SpringForceGenerator(body.GetPosition(), &legL, legL.GetPosition(), 10.f, 20.f), &legL)); //Left Leg (Particles Bungee)
	//bodyParts.push_back(new BodyPart(new SpringForceGenerator(body.GetPosition(), &legR, legR.GetPosition(), 10.f, 20.f), &legR)); //Right Leg (Particles Bungee)

	//Body suit la souris
	//bodyParts.push_back(new BodyPart(new SpringForceGenerator(reticle.GetPosition(), &body, body.GetPosition(), 40.4f, 1), &body)); //Corps suit souris (Particles Spring)
	//
	////Spring Fixed
	//RigidBody fixedPart = RigidBody(Color::Yellow, 30);
	//fixedPart.SetPosition(Vector3D(300.0f, 200.0f));
	//Vector3D sFixedPos = fixedPart.GetPosition() + Vector3D(0, -80.0f);
	//bodyParts.push_back(new BodyPart(new GravityForceGeneratorBody(Vector3D(0, -100.f)), &fixedPart)); //Gravite
	//bodyParts.push_back(new BodyPart(new SpringForceGenerator(sFixedPos, &fixedPart, fixedPart.GetPosition(), 3.f, 100.f), &fixedPart)); //Fixed Particles (Fixed Spring)
	//physicW.AddRigidBody(&fixedPart);
	//fuseParticles.push_back(&fixedPart);

	////Rod Collision
	//ParticleRod* cableHead = new ParticleRod(35);
	//cableHead->setParticle1(&head);
	//cableHead->setParticle2(&body);
	//physicW.AddContactGenerator(cableHead);

	////Cable Collision
	//ParticleCable* cableArmL = new ParticleCable(55, 0.6f);
	//cableArmL->setParticle1(&armL);
	//cableArmL->setParticle2(&body);
	//physicW.AddContactGenerator(cableArmL);

	//ParticleCable* cableArmR = new ParticleCable(55, 0.6f);
	//cableArmR->setParticle1(&armR);
	//cableArmR->setParticle2(&body);
	//physicW.AddContactGenerator(cableArmR);

	//ParticleCable* cableLegL = new ParticleCable(65, 0.6f);
	//cableLegL->setParticle1(&legL);
	//cableLegL->setParticle2(&body);
	//physicW.AddContactGenerator(cableLegL);

	//ParticleCable* cableLegR = new ParticleCable(65, 0.3f);
	//cableLegR->setParticle1(&legR);
	//cableLegR->setParticle2(&body);
	//physicW.AddContactGenerator(cableLegR);

	//Ajout des forces dans le gestionnaire de physiques
	for (BodyPart* part : bodyParts)
		physicW.AddEntry(part->particule, part->forceGen);


	//TP1 Part
	srand(time(NULL));

	RenderWindow window(VideoMode(800, 600), "TP3", Style::Default);
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
		/*if (Keyboard::isKeyPressed(Keyboard::O))
		{
			RigidBody* lastPart = fuseParticles[fuseParticles.size() - 1];
			float lastRadius = lastPart->GetRadius();

			//Ne pas split lorsque dimensions trop petites
			if (lastRadius > 1 && peutSplit) {
				RigidBody* newBlob = new RigidBody(Color::Yellow, lastRadius / 2);
				newBlob->SetPosition(Vector3D(lastPart->GetPosition()));
				newBlob->test = true;

				Vector3D sFixedPos = newBlob->GetPosition();
				GravityForceGeneratorBody* partiGravity = new GravityForceGeneratorBody(Vector3D(0, 300.f)); //Gravite
				//SpringBungee* partiSpring = new SpringBungee(lastPart, 10.f, 5.f); //Fixed Particles (Fixed Spring)
				bodyParts.push_back(new BodyPart(new SpringForceGenerator(sFixedPos, &fixedPart, fixedPart.GetPosition(), 3.f, 100.f), &fixedPart)); //Fixed Particles (Fixed Spring)

				physicW.AddEntry(newBlob, partiGravity);
				//physicW.AddEntry(newBlob, partiSpring);
				physicW.AddRigidBody(newBlob);
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
			RigidBody* lastPart = fuseParticles[fuseParticles.size() - 1];
			RigidBody* prevPart = fuseParticles[fuseParticles.size() - 2];
			float lastRadius = lastPart->GetRadius();

			if (peutFuse) {
				physicW.RemoveRigidBody(lastPart);
				physicW.RemoveEntries(lastPart);
				fuseParticles.erase(fuseParticles.end() - 1);

				prevPart->SetRadius(lastPart->GetRadius() * 2);

				peutFuse = false;
			}
		}
		else
			peutFuse = true;*/

		mousePosWindow = Vector2f(Mouse::getPosition(window));

		reticle.SetPosition(Vector3D(mousePosWindow.x, mousePosWindow.y));
		//reticle.Integrate(0);
		reticleIn.setPosition(mousePosWindow);

		//TP2
		physicW.StartFrame();


		//TP3 : Demo 1 - Propulsion angulaire Cube
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			if (!spacePressed) {
				//Apply force d�part
				//armL.SetPosition(Vector3D(300, 300));
				//armL.AddForce(Vector3D(10000, 0, 0));
				//armL.AddTorque(Vector3D(1000, 0, 0));

				armL.AddForceAtPoint(Vector3D(1, 0, 0), Vector3D(0, 100, 0));
				spacePressed = true;
			}
		}
		else
			spacePressed = false;

		if (!hasCollided)
		{
			car1.AddForce(Vector3D(-500, 0, 0));
			car2.AddForce(Vector3D(500, 0, 0));

			float distance = sqrtf(powf(car1.GetPosition().x - car2.GetPosition().x, 2) + powf(car1.GetPosition().y - car2.GetPosition().y, 2));

			if (distance <= 50.f)
			{
				hasCollided = true;
				car1.AddForceAtBodyPoint(Vector3D(1, 0, 0), Vector3D(0, 100, 0));
				car2.AddForceAtBodyPoint(Vector3D(-1, 0, 0), Vector3D(0, -100, 0));
				car1.AddForce(Vector3D(10000, 0, 0));
				car2.AddForce(Vector3D(-10000, 0, 0));
			}
		}


		physicW.RunPhysics(deltaTime.asSeconds());

		//Draw
		window.clear();

		//TP2
		//for (BodyPart* part : bodyParts)
			//window.draw(part->particule->shape);
		window.draw(body.shape);
		//window.draw(head.shape);
		window.draw(armL.shape);
		window.draw(car1.shape);
		window.draw(car2.shape);
		//window.draw(armR.shape);
		//window.draw(legL.shape);
		//window.draw(legR.shape);

		//Draw Lignes Fusion
		if (fuseParticles.size() >= 2) {
			//fuseParticles[1]->shape.setPosition(100, 100);
			float a = 0.1f;
		}

		for (RigidBody* part : fuseParticles) {
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