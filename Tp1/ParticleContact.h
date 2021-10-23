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

	//direction normalis�e du contact
	Vector3D contactNormal;

	//Autres m�thodes...

public:
	//R�soud v�locit� et interpr�n�tration
	void Resoudre(float duration);

	//Retourne la separationVelocity des particules
	float CalculateSeparatingVelocity();

private:
	//G�rer l'impulsion pour cette collision
	void ResolveVelocity();

	//G�rer l'interprenetration pour cette collision
	void ResolveInterprenetration();
};

