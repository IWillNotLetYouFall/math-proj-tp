#include "OctTree.h"
#include <iostream>

#define LeftTopFront 0
#define RightTopFront 1
#define LeftBotFront 2
#define RightBotFront 3
#define LeftTopBack 4
#define RightTopBack 5
#define LeftBotBack 6
#define RightBotBack 7

OctTree::OctTree(Vector3D position, Vector3D size)
{
	this->position = position;
	this->size = size;
	std::cout << "New node - Pos:" << position.ToString() << std::endl;
}

void OctTree::InsertNew(Box* box)
{
	//Début OctTree - Attribue mur à toutes les directions

	Vector3D position = box->body->GetPosition();
	Insert(position, 0);
}

void OctTree::InsertCall(Vector3D& point, int depth)
{
	int posIndex = ObtIndexNode(point);
	if (posIndex == -1) {
		std::cout << "Point could not be found (error!)" << std::endl;
		return;
	}
	child[posIndex]->Insert(point, depth + 1);
}

void OctTree::Insert(Vector3D& point, int depth)
{
	if (Find(point)) {
		std::cout << "Point has been found inside Tree!" << std::endl;
		return;
	}
	if (!IsContained(point)) {
		std::cout << "Point is out of bounds!" << std::endl;
		return;
	}

	//If Oct-Tree is a leaf
	if (child.size() != 8) {
		points.push_back(&point);
		std::cout << "Point inserted into Leaf - Leaf pos:" << position.ToString() << std::endl;
		if (points.size() <= maxLeafs)
			return;

		//If the leafs amount has been maxed out + can create branch, split.
		if (depth < maxIterations)
		{
			SplitTree(depth);
			for (int n = 0; n < points.size(); n++)
				InsertCall(*points[n], depth);
			points.clear();
		}
	}
	else
		InsertCall(point, depth); //If Oct-Tree isn't a leaf
}

bool OctTree::Find(Vector3D& point)
{
	if (!IsContained(point))
		return false; //Point out of border

	//Si l'oct-tree n'est pas une feuille
	if (child.size() == 8) {
		//Section va appeller Tree récusrivement jusqu'à avoir cherché dans toutes les zones potentielles
		//Un for loop va être présent lorsque mode multi-zones va être fait.
		int posIndex = ObtIndexNode(point);
		if (posIndex == -1) {
			std::cout << "Point could not be found (error!)" << std::endl;
			return false;
		}
		return child[posIndex]->Find(point);
	}
	
	//Suite est pour le moment un single check. Remplacer par un for loop lorsque plusieurs points sont ajoutés.
	//Retourne true lorsque objet trouvé. Appelé à la fin de la récursion
	for (int i = 0; i < points.size(); i++)
		if (points[i]->x == point.x && points[i]->y == point.y && points[i]->z == point.z)
			return true;

	return false;
}

bool OctTree::IsContained(Vector3D& point)
{
	return !(point.x < position.x - (size.x / 2)
		|| point.x > position.x + (size.x / 2)
		|| point.y < position.y - (size.y / 2)
		|| point.y > position.y + (size.y / 2)
		|| point.z < position.z - (size.z / 2)
		|| point.z > position.z + (size.z / 2));
}

int OctTree::ObtIndexNode(Vector3D& point)
{
	// (XPOS = à Droite)(YPOS = Vers le Bas)(ZPOS = Front Vers l'écran)
	if (point.x <= position.x)
		if (point.y <= position.y)
			return point.z <= position.z ? LeftTopBack : LeftTopFront;
		else
			return point.z <= position.z ? LeftBotBack : LeftBotFront;
	else
		if (point.y <= position.y)
			return point.z <= position.z ? RightTopBack : RightTopFront;
		else
			return point.z <= position.z ? RightBotBack : RightBotFront;
	return -1;
}

void OctTree::SplitTree(int depth)
{
	Vector3D qtSize = size / 4;
	Vector3D halfSize = size / 2;
	vector<Vector3D> newPos;

	std::cout << "Too many leafs - Spliting into 8 at depth " << depth+1 << " - New size:" << halfSize.ToString() << std::endl;

	//Définition des positions de chaque nouvelle branche
	newPos.push_back(Vector3D(position.x - qtSize.x, position.y - qtSize.y, position.z + qtSize.z)); //LeftTopFront
	newPos.push_back(Vector3D(position.x + qtSize.x, position.y - qtSize.y, position.z + qtSize.z)); //RightTopFront
	newPos.push_back(Vector3D(position.x - qtSize.x, position.y + qtSize.y, position.z + qtSize.z)); //LeftBotFront
	newPos.push_back(Vector3D(position.x + qtSize.x, position.y + qtSize.y, position.z + qtSize.z)); //RightBotFront
	newPos.push_back(Vector3D(position.x - qtSize.x, position.y - qtSize.y, position.z - qtSize.z)); //LeftTopBack
	newPos.push_back(Vector3D(position.x + qtSize.x, position.y - qtSize.y, position.z - qtSize.z)); //RightTopBack
	newPos.push_back(Vector3D(position.x - qtSize.x, position.y + qtSize.y, position.z - qtSize.z)); //LeftBotBack
	newPos.push_back(Vector3D(position.x + qtSize.x, position.y + qtSize.y, position.z - qtSize.z)); //RightBotBack

	//Ajout des OctTrees child avec leurs posiitons
	child.clear();
	for (int i = 0; i < 8; i++)
		child.push_back(new OctTree(newPos[i], halfSize));

	//Assigner Cotés aux nouvelles séparations (même que parent) 
	//Détermine les murs de fin de Octtree liés à la zone.

}

vector<OctTree*> OctTree::GetBoundingZones(Box* box)
{
	vector<OctTree*> boundingZones;

	//Retourne vide si box pas dans Oct-Tree
	Vector3D position = box->body->GetPosition();
	if (!Find(position))
		return boundingZones;

	//Similaire à Find(), mais au lieu de retourner true, va retourner la liste zones + current



	return boundingZones;
}

bool OctTree::CheckBroad(Box* box, Plane* plane)
{
	//Fait un Broad Collision Check entre box(boundingSphere) et plane

	//Convertis Box en Sphere

	//Call BroadCheck
	bool broadCollision = false; //Broad Method Call

	return broadCollision;
}

bool OctTree::CheckBroad(Box* box1, Box* box2)
{
	//Fait un Broad Collision Check entre box1(boundingSphere) et box2("")

	//Convertis Box1 en Sphere

	//Convertis Box2 en Sphere

	//Call BroadCheck
	bool broadCollision = false; //Broad Method Call

	return broadCollision;
}

vector<Plane*> OctTree::GetBroadPlanes(Box* box)
{
	vector<Plane*> planeList;

	//Obt Liste Collisions avec Box

	//Check quel cotés a un potentiel de collision dans liste recue et PlaneCheck

	//Obtenir les planes associés aux cotés positifs

	//For loop BroadCheck pour avoir que les planes ayant un broad phase check positif.
	vector<Plane*> boundingPlanes;
	for (int i = 0; i < planeList.size(); i++)
		if (CheckBroad(box, planeList[i]))
			boundingPlanes.push_back(planeList[i]);

	//Retourne les planes!

	return boundingPlanes;
}

vector<Box*> OctTree::GetBroadBoxes(Box* box)
{
	vector<Box*> boxList;

	//Obt Liste Collisions avec Box

	//Obt Boxes présents dans liste et filtrer afin de ne pas avoir de doublons

	//For loop BroadCheck pour avoir que les planes ayant un broad phase check positif.
	vector<Box*> boundingBoxes;
	for (int i = 0; i < boxList.size(); i++)
		if (CheckBroad(box, boxList[i]))
			boundingBoxes.push_back(boxList[i]);

	return boundingBoxes;
}
