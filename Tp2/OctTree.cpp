#include "OctTree.h"
#include <iostream>

OctTree::OctTree(float x, float y, float z)
{
	position = Vector3D(x, y, z);
}

void OctTree::Insert(Vector3D& point)
{
	//if (Find(point)) {
	//	std::cout << "Point is already in oct-tree!" << std::endl;
	//	return;
	//}
	//if (!IsContained(point)) {
	//	std::cout << "Point is out of bounds!" << std::endl;
	//	return;
	//}

}
