#pragma once
#include "Particule.h"

class Bomb : public Particule
{
private:
	const float radius = 24.f;
	float masse = 3;

public:
	Bomb();
	Bomb(const Bomb& base);
};

