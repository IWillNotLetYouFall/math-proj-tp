#include "GameObject.h"

GameObject::GameObject(float radius, RenderWindow& window)
{
	this->window = &window;
	this->radius = radius;
}
