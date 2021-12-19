#pragma once
#include "Plane.h"
#include <vector>
using namespace std;

class PlaneCheck
{
public:
	Plane* onTopWall = NULL;
	Plane* onBottomWall = NULL;
	Plane* onLeftWall = NULL;
	Plane* onRightWall = NULL;
	Plane* onFrontWall = NULL;
	Plane* onBackWall = NULL;

public:
	vector<Plane*> GetPlanes();
};

