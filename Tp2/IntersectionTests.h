#pragma once
#include "Plane.h"
#include "Box.h"
#include "Sphere.h"

class IntersectionTests
{
public:
	static bool SphereSphereIntersection(const Sphere& sphere1, const Sphere& sphere2);
	static bool SpherePlaneIntersection(const Sphere& sphere, const Plane& plane);
	static bool BoxBoxIntersection(const Box& box1, const Box& box2);
	static bool BoxPlaneIntersection(Box& box, const Plane& plane);
};

