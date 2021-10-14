#pragma once
#include "Particule.h"

class Laser : public Particule
{
private:
	const float radius = 9.f;
	float masse = 0.1f;

public:
	Laser();
	Laser(const Laser& base);
	void Integrate(float delta) override;
};

