#include "Box.h"

float Box::TransformToAxis(const Vector3D& axis)
{
	//std::cout << "AXE " << GetAxis(0).ToString();
	float val = halfsize.x * abs(GetAxis(0).ScalarProduct(axis));
	val += halfsize.y * abs(GetAxis(1).ScalarProduct(axis));
	val += halfsize.z * abs(GetAxis(2).ScalarProduct(axis));
	return val;
}
