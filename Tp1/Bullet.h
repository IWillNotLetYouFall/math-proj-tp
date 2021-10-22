#pragma once
#include "Particule.h"

class Bullet : public Particule
{
private:
	const float radius = 4.f;
	float masse = 3;

public:
	Bullet();
	Bullet(const Bullet& base);
	void Integrate(float delta) override;
};

