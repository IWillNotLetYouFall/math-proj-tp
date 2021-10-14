#pragma once
#include "Particule.h"

class Fireball : public Particule
{
private:
	const float radius = 18.f;
	float masse = 3;

public:
	Fireball();
	Fireball(const Fireball& base);
};

