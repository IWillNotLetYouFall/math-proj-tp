#include "Character.h"

Character::Character(Color color, Vector3D pos, float radius, RenderWindow& window)
{
	turret = new Turret(Color::Blue, pos, radius * 1.2f, window);
	this->window = &window;
	this->radius = radius;
	shape = RectangleShape();
	shape.setFillColor(color);
	shape.setSize(Vector2f(radius * 2, radius * 2));
	shape.setOrigin(radius, radius);
	shape.setPosition(pos.x, pos.y + 5.f);
}

void Character::Update(RectangleShape& wall, float delta)
{
	if (Keyboard::isKeyPressed(Keyboard::A))
		{
			if (shape.getPosition().x - 8.f < 25.f)
			{
				shape.setPosition(25.f, shape.getPosition().y);
				turret->SetPosition(Vector3D(25.f, turret->GetPosY()));
			}
			else
			{
				shape.move(-8.f, 0.f);
				turret->Move(Vector3D(-8.f, 0.f));
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			if (shape.getPosition().x + 8.f > wall.getPosition().x - 25.f)
			{
				shape.setPosition(wall.getPosition().x - radius, shape.getPosition().y);
				turret->SetPosition(Vector3D(wall.getPosition().x - radius, turret->GetPosY()));
			}
			else
			{
				shape.move(8.f, 0.f);
				turret->Move(Vector3D(8.f, 0.f));
			}
		}
		if (grounded)
		{
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				grounded = false;
				vsp = -15.f;
			}
		}
		else
			vsp += 0.8f;

		shape.move(0.f, vsp);
		turret->Move(Vector3D(0.f, vsp));

		if (shape.getPosition().y > window->getSize().y - 25.f)
		{
			shape.setPosition(shape.getPosition().x, window->getSize().y - radius);
			turret->SetPosition(Vector3D(shape.getPosition().x, window->getSize().y - 35.f));
			grounded = true;
			vsp = 0.f;
		}
		turret->Update(delta);
}

void Character::Draw()
{
	window->draw(shape);
	turret->Draw();
}
