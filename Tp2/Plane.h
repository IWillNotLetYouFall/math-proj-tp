#pragma once

#include "Primitive.h"


//Mur infini
class Plane : public Primitive
{

public:
	Vector3D normal; //Direction mur fait face
	float offset; //D�calage mur par rapport � direction, �paisseur infinie derri�re offset.

public:
	//Plane();
};