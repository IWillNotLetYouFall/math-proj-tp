#pragma once

#include "Primitive.h"


//Mur infini
class Plane : public Primitive
{

public:
	Vector3D normal; //Direction mur fait face
	float offset; //Décalage mur par rapport à direction, épaisseur infinie derrière offset.

public:
	//Plane();
};