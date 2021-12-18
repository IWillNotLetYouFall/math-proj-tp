#include "OctTree.h"
#include <iostream>

#define TopLeftFront 0
#define TopRightFront 1
#define BotLeftFront 2
#define BotRightFront 3
#define TopLeftBack 4
#define TopRightBack 5
#define BotLeftBack 6
#define BotRightBack 7

OctTree::OctTree(float x, float y, float z)
{
	position = Vector3D(x, y, z);
}

void OctTree::Insert(Vector3D& point)
{
	if (Find(point)) {
		//std::cout << "Point is already in oct-tree!" << std::endl;
		return;
	}
	if (!IsContained(point)) {
		std::cout << "Point is out of bounds!" << std::endl;
		return;
	}


}

bool OctTree::Find(Vector3D& point)
{
	if (!IsContained(point)) {
		std::cout << "Point is out of bounds(Find function)!" << std::endl;
		return false;
	}

	int posIndex = -1;
	posIndex = ObtIndexNode(point);


	return false;
}

bool OctTree::IsContained(Vector3D& point)
{
	return !(point.x < position.x - (size.x / 2)
		|| point.x > position.x - (size.x / 2)
		|| point.y < position.y - (size.y / 2)
		|| point.y > position.y - (size.y / 2)
		|| point.z < position.z - (size.z / 2)
		|| point.z > position.z - (size.z / 2));
}

int OctTree::ObtIndexNode(Vector3D& point)
{
	// (XPOS = à Droite)(YPOS = Vers le Bas)(ZPOS = Front Vers l'écran)
	if (point.x <= position.x)
		if (point.y <= position.y)
			return point.z <= position.z ? TopLeftBack : TopLeftFront;
		else
			return point.z <= position.z ? BotLeftBack : BotLeftFront;
	else
		if (point.y <= position.y)
			return point.z <= position.z ? TopRightBack : TopRightFront;
		else
			return point.z <= position.z ? BotRightBack : BotRightFront;
	return -1;
}
