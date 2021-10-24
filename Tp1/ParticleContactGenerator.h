#pragma once
#include "ParticleContact.h"
#include "Vector3D.h"
#include <cmath>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "Particule.h"

class ParticleContactGenerator
{
public:
	// Prend un array de contact et le nombre de contacts restants � g�n�rer
	virtual unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;

};

