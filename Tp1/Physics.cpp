#include "Physics.h"

Physics* Physics::instance;

void Physics::NewInstance()
{
	instance = new Physics();
}

Physics Physics::GetInstance()
{
	return *instance;
}

void Physics::AddCircle(CircleShape* circle)
{
	circles.push_back(circle);
}

void Physics::RemoveCircle(CircleShape* circle)
{
	for (int i = 0; i < circles.size(); i++)
	{
		if (circles[i] == circle) {
			circles.erase(circles.begin() + i);
			return;
		}
	}
}

void Physics::AddRectangle(RectangleShape* rectangle)
{
	rectangles.push_back(rectangle);
}

void Physics::RemoveRectangle(RectangleShape* rectangle)
{
	for (int i = 0; i < rectangles.size(); i++)
	{
		if (rectangles[i] == rectangle) {
			rectangles.erase(rectangles.begin() + i);
			return;
		}
	}
}

void Physics::RemoveContact(Contact* contact)
{
	for (int i = 0; i < contacts.size(); i++)
	{
		if (contacts[i] == contact) {
			contacts.erase(contacts.begin() + i);
			return;
		}
	}
}

Contact* Physics::CollisionDetection(Shape* shape, float weight, Vector3D vel, float delta)
{
	Contact* contact = GetCollidedContact(shape);
	if (contact == NULL) {
		Vector2f posShape = shape->getPosition();
		//Vector3D posSim = Vector3D(posShape.x, posShape.y) + (vel * delta);

		//Check Circle Coll
		CircleShape* circle = dynamic_cast<CircleShape*>(shape);
		if (circle != NULL) {
			contact = ContactBetweenCircles((vel * delta), weight, circle);
		}
	}

	return contact;
}

Contact* Physics::GetCollidedContact(Shape* shape)
{
	Contact* contact = NULL;
	for (Contact* ct : contacts) {
		if (ct->collided->shape == shape) {
			contact = ct;
			break;
		}
	}
	
	return contact;
}

Contact* Physics::ContactBetweenCircles(Vector3D vel, float weight, CircleShape* mainCircle)
{
	//Obt attributs cercle principal
	Vector3D posMain = Vector3D(mainCircle->getPosition().x, mainCircle->getPosition().y);
	float radiusCircle = mainCircle->getRadius();
	Collider mainCollider = Collider(mainCircle, posMain, vel, weight);


	Vector3D posSecCircle;
	float radiusSecCircle;
	Contact* contact = NULL;
	for (CircleShape* circle : circles) {
		if (circle == mainCircle)
			continue;
		posSecCircle = Vector3D(circle->getPosition().x, circle->getPosition().y);
		radiusSecCircle = circle->getRadius();

		//Verif
		Vector3D ligneDist = posSecCircle - posMain;
		float distInterpolated = (radiusCircle + radiusSecCircle) - ligneDist.GetNorm();
		if (distInterpolated >= 0) {
			//Collision
			float weightSec = 9999;
			Vector3D positionSec = Vector3D(circle->getPosition().x, circle->getPosition().y);
			Vector3D velSec = Vector3D();
			Collider secCollider = Collider(circle, positionSec, velSec, weightSec);
			
			//LigneDist = placer dépendant du ratio masse TODO
			float ratioDist = weightSec / (weightSec + weight);
			Vector3D pointContact = ligneDist.Normalize() * (radiusCircle - ratioDist * distInterpolated) + posMain;
			Contact* newContact = new Contact(&mainCollider, &secCollider, pointContact);
			contacts.push_back(newContact);
			return newContact;
		}
	}

	return contact;
}
