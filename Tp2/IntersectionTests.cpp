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
