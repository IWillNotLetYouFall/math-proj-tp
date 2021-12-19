#include "PlaneCheck.h"

vector<Plane*> PlaneCheck::GetPlanes()
{
    vector<Plane*> planeList;

    if (onTopWall != NULL) planeList.push_back(onTopWall);
    if (onBottomWall != NULL) planeList.push_back(onBottomWall);
    if (onLeftWall != NULL) planeList.push_back(onLeftWall);
    if (onRightWall != NULL) planeList.push_back(onRightWall);
    if (onFrontWall != NULL) planeList.push_back(onFrontWall);
    if (onBackWall != NULL) planeList.push_back(onBackWall);

    return planeList;
}
