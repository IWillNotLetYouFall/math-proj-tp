#pragma once

#include "Vector3D.h"

class Octree
{
	Vector3D position;
	Octree* child[8];
	bool hasChildren = false;
	float halfsize = -1;

public:

	Octree(float x, float y, float z)
	{
		position = Vector3D(x, y, z);
	}

	Octree getChild(int index)
	{
		if(index >= 0 && index < 8 && hasChildren)
			return *child[index];
	}

	Vector3D getPosition()
	{
		return position;
	}

	float getHalfsize()
	{
		return halfsize;
	}

	int getChildIndex(const Vector3D& object)
	{
		int index = 0;
		if (object.x > position.x) index += 1;
		if (object.y > position.y) index += 2;
		if (object.z > position.z) index += 4;
		return index;
	}

	void subdivide(float size)
	{
		halfsize = size;
		hasChildren = true;
		child[0] = new Octree(position.x - halfsize, position.y - halfsize, position.z - halfsize);
		child[1] = new Octree(position.x + halfsize, position.y - halfsize, position.z - halfsize);
		child[2] = new Octree(position.x - halfsize, position.y + halfsize, position.z - halfsize);
		child[3] = new Octree(position.x - halfsize, position.y - halfsize, position.z + halfsize);
		child[4] = new Octree(position.x + halfsize, position.y + halfsize, position.z - halfsize);
		child[5] = new Octree(position.x + halfsize, position.y - halfsize, position.z + halfsize);
		child[6] = new Octree(position.x - halfsize, position.y + halfsize, position.z + halfsize);
		child[7] = new Octree(position.x + halfsize, position.y + halfsize, position.z + halfsize);
	}
};