#include "Turret.h"

Turret::Turret(Color color, Vector3D pos, float radius, RenderWindow& window) : GameObject(radius, window)
{
	shape = new RectangleShape(Vector2f(radius, radius * 2));
	shape->setFillColor(color);
	shape->setOrigin(radius / 2, radius);
	shape->setPosition(100, window.getSize().y - radius + 5.f);
}

void Turret::Update(float delta)
{
	UpdateAim();
	UpdateWeapon();
	UpdateShoot();
	UpdateBullets(delta);
}

void Turret::Draw()
{
	window->draw(*shape);

	for (size_t i = 0; i < bullets.size(); i++)
	{
		//window->draw(*bullets[i].shape);
		bullets[i]->Draw(window);
	}
}

void Turret::SetPosition(Vector3D pos)
{
	shape->setPosition(pos.x, pos.y);
}

float Turret::GetPosY()
{
	return shape->getPosition().y;
}

void Turret::Move(Vector3D pos)
{
	shape->move(pos.x, pos.y);
}

void Turret::UpdateAim()
{
	turretCenter = Vector2f(shape->getPosition());
	mousePosWindow = Vector2f(Mouse::getPosition(*window));
	aimDir = mousePosWindow - turretCenter;
	aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + (float)pow(aimDir.y, 2));

	float PI = 3.14159265f;
	float deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / PI;
	shape->setRotation(deg + 90);
}

void Turret::UpdateWeapon()
{
	//Switch ammo
	if (Keyboard::isKeyPressed(Keyboard::Num1))
		currentBullet = 0;
	else if (Keyboard::isKeyPressed(Keyboard::Num2))
		currentBullet = 1;
	else if (Keyboard::isKeyPressed(Keyboard::Num3))
		currentBullet = 2;
	else if (Keyboard::isKeyPressed(Keyboard::Num4))
		currentBullet = 3;
}

void Turret::UpdateShoot()
{
	//Shooting
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (canShoot) {
			if (currentBullet == 0)
				baseParticle = new Laser();
			else if (currentBullet == 1)
				baseParticle = new Bullet();
			else if (currentBullet == 2)
				baseParticle = new Fireball();
			else if (currentBullet == 3)
				baseParticle = new Bomb();

			baseParticle->position = Vector3D(turretCenter.x, turretCenter.y);
			baseParticle->velocite = Vector3D(aimDirNorm.x, aimDirNorm.y) * baseParticle->maxSpeed;
			canShoot = false;
			bullets.push_back(baseParticle);
		}
	}
	else if (!canShoot)
		canShoot = true;
}

void Turret::UpdateBullets(float delta)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Integrate(delta);

		//Collisions Écran
		if (bullets[i]->position.x < 0 || bullets[i]->position.x > window->getSize().x
			|| bullets[i]->position.y < 0 || bullets[i]->position.y > window->getSize().y)
		{
			bullets.erase(bullets.begin() + i);
		}
		else
		{
			//Collisions Env.
			//for (size_t k = 0; k < enemies.size(); k++)
			//{
			//	if (bullets[i].shape.getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
			//	{
			//		bullets.erase(bullets.begin() + i);
			//		enemies.erase(enemies.begin() + k);
			//		break;
			//	}
			//	else if (bullets[i].shape.getGlobalBounds().intersects(wall.getGlobalBounds()))
			//	{
			//		bullets.erase(bullets.begin() + i);
			//		break;
			//	}
			//}
		}
	}
}
