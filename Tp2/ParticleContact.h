#pragma once
#include "Particule.h"

class ParticleContact
{
public:
	//Particle[0] is A, [1] is B
	Particule* particle[2];

	//Valeur entre 0 et 1
	//elasticness de la collision
	float restitution;

	//Distance penetration contact
	float penetration;

	//direction normalisée du contact
	Vector3D contactNormal;

	//Autres méthodes...

public:
	//Résoud vélocité et interprénétration
	void Resolve(float duration);

	//Retourne la separationVelocity des particules
	float CalculateSeparatingVelocity();

private:
	//Gérer l'impulsion pour cette collision + Gestion repos
	void ResolveVelocity(float duration);

	//Gérer l'interprenetration pour cette collision
	void ResolveInterpenetration();
};

