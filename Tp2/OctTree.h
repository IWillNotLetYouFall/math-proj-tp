#pragma once
#include "Vector3D.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include "Rigidbody.h"
#include "Plane.h"
#include "Box.h"
#include "Sphere.h"

using namespace std;

class OctTree
{
private:
	int maxLeafs = 2;
	int maxIterations = 3;

public :
	Vector3D position;
	Vector3D size;
	vector<OctTree*> child; // Length = 8 pour oct
	vector<Vector3D*> points; //Temp, deviendra BoundingSphere ou Primitive

private:
	void InsertCall(Vector3D& point, int depth);
	void Insert(Vector3D& point, int depth);
	bool Find(Vector3D& point);
	//OctTree[] FindZones(Vector3D& point);
	//Coll[] GetCollisions(OctTree[] zones, Point& exclus);
	bool IsContained(Vector3D& point);
	int ObtIndexNode(Vector3D& point);
	void SplitTree(int depth);
	//Part2
	vector<OctTree*> GetBoundingZones(Box* box);
	bool CheckBroad(Box* box, Plane* plane);
	bool CheckBroad(Box* box1, Box* box2);

public:
	OctTree(Vector3D position, Vector3D size);
	void InsertNew(Box* box);
	vector<Plane*> GetBroadPlanes(Box* box);
	vector<Box*> GetBroadBoxes(Box* box);
};

