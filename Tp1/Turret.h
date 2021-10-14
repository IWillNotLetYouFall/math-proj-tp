#pragma once
#include "GameObject.h"
#include "Particule.h"
#include "Laser.h"
#include "Fireball.h"
#include "Bullet.h"
#include "Bomb.h"

class Turret : GameObject
{
private:
	bool canShoot = true;
	Particule* baseParticle = new Laser();
	std::vector<Particule*> bullets;
	Vector2f turretCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;

	//Input
	int currentBullet = 0;

public:
	Turret(Color color, Vector3D pos, float radius, RenderWindow& window);
	void Update(float delta) override;
	void Draw() override;
	void Test() {};
	void SetPosition(Vector3D pos);
	float GetPosY();
	void Move(Vector3D pos);

private:
	void UpdateAim();
	void UpdateWeapon();
	void UpdateShoot();
	void UpdateBullets(float delta);
};

