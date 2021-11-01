#pragma once
#include "Particule.h"

class Laser : public Particule
{
private:
	float masse = 0.1f;
public:
	float maxSpeed = 1500.f;

public:
	Laser();
	Laser(const Laser& base);
};

