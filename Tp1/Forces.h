#pragma once
#include "Particule.h"

class Forces
{
public:
	// interface function
	virtual void UpdateForce(Particule* particle, float duration) = 0;
};