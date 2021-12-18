#pragma once
#include "Vector3D.h"

class OctTree
{
	Vector3D position;
	OctTree* child[8];
	bool hasChildren = false;
	float halfsize = -1;

	int maxDepth = 3;
	int maxElements = 2;

public:
	OctTree(float x, float y, float z);
	OctTree getChild(int index)
	{
		if (index >= 0 && index < 8 && hasChildren)
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
		child[0] = new OctTree(position.x - halfsize, position.y - halfsize, position.z - halfsize);
		child[1] = new OctTree(position.x + halfsize, position.y - halfsize, position.z - halfsize);
		child[2] = new OctTree(position.x - halfsize, position.y + halfsize, position.z - halfsize);
		child[3] = new OctTree(position.x + halfsize, position.y + halfsize, position.z - halfsize);
		child[4] = new OctTree(position.x - halfsize, position.y - halfsize, position.z + halfsize);
		child[5] = new OctTree(position.x + halfsize, position.y - halfsize, position.z + halfsize);
		child[6] = new OctTree(position.x - halfsize, position.y + halfsize, position.z + halfsize);
		child[7] = new OctTree(position.x + halfsize, position.y + halfsize, position.z + halfsize);
	}

public :
	Vector3D size;
public:
	void Insert(Vector3D& point);
	bool Find(Vector3D& point);
	bool IsContained(Vector3D& point);
};

