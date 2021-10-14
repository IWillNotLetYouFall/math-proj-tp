#pragma once
#include "Vector3D.h"
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>

using namespace sf;

class GameObject
{
protected:
	Shape* shape;
	float radius;
	RenderWindow* window;
public:
	GameObject(float radius, RenderWindow& window);
	virtual void Update(float delta) {};
	virtual void Draw() {};
};

