#include "IntersectionTests.h"

bool IntersectionTests::BoxPlaneIntersection(Box& box, const Plane& plane)
{
    Vector3D planeDir = plane.normal;

    float radiusProjected = box.TransformToAxis(planeDir);
    //std::cout << "Radius Projete : " << radiusProjected;

    float distanceBox = planeDir.ScalarProduct(box.GetAxis(3)) - radiusProjected;
    //std::cout << " Dist Box : " << plane.offset - distanceBox << std::endl;
    return distanceBox <= plane.offset;
}

bool IntersectionTests::SpherePlaneIntersection(const Sphere& sphere, const Plane& plane)
{
    // Find the distance from the origin
    float ballDistance = sphere.body->getRotation().ScalarProduct(plane.normal) - sphere.radius;

    // Check for the intersection
    return ballDistance <= plane.offset;
}