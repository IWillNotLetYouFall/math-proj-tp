#pragma once
#include "Vector3D.h"
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include "Turret.h"

using namespace sf;

class Character
{
protected:
	Turret* turret;
	float radius;
	RenderWindow* window;
	RectangleShape shape;
	bool grounded = true;
	bool canShoot = true;
	float vsp = 0.f;
public:
	Character(Color color, Vector3D pos, float radius, RenderWindow& window);
	void Update(RectangleShape& wall, float delta);
	void Draw();
};

