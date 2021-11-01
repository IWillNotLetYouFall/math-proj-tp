#pragma once
#include "Particule.h"

class ParticleForceGenerator
{
public:
<<<<<<< HEAD:Tp1/Bullet.h
	Bullet();
	Bullet(const Bullet& base);
	void Integrate(float delta) override;
};

=======
	// interface function
	virtual void UpdateForce(Particule* particle, float duration) = 0;
};
>>>>>>> GettingRevert:Tp2/ParticleForceGenerator.h
