#pragma once

#include "Forces.h"
#include "Vector3D.h"

//Spring between particle and fixed object

class SpringFixed : public Forces
{
	//other anchor
	Vector3D m_anchor;

	//Spring constant
	float m_k;

	float m_restLenght;

public:
	SpringFixed(Vector3D anchor, float k, float restLenght) : m_anchor(anchor), m_k(k), m_restLenght(restLenght) {};

	//apply hooke's law from particles position
	void UpdateForce(Particule* particle, float duration);
};