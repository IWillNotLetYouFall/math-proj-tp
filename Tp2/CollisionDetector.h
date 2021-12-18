#pragma once
#include "Vector3D.h"
#include <cmath>
#include <iostream>
#include <string>
#include "Plane.h"
#include "Box.h"
#include "Sphere.h"
#include "IntersectionTests.h"
#include "CollisionData.h"

class CollisionDetector
{
public:
	static unsigned SphereSphereDetect(const Sphere& sphere1, const Sphere& sphere2, CollisionData* data);
	static unsigned SpherePlaneDetect(const Sphere& sphere, const Plane& plane, CollisionData* data);
	static unsigned BoxBoxDetect(const Box& box1, const Box& box2, CollisionData* data);
	static unsigned BoxPlaneDetect(Box& box, Plane& plane, CollisionData* data);
	static unsigned BoxPointDetect(const Box& box, const Vector3D& point, CollisionData* data);
	static unsigned BoxSphereDetect(const Box& box, const Sphere& sphere, CollisionData* data);
};

