#include "CollisionDetector.h"




unsigned CollisionDetector::BoxPlaneDetect(Box& box, Plane& plane, CollisionData* data)
{
	if (!data->HasContactsLeft()) return 0;

	if (!IntersectionTests::BoxPlaneIntersection(box, plane)) return 0;

	static float mults[8][3] = { {1,1,1},{-1,1,1},{1,-1,1},{-1,-1,1},
						   {1,1,-1},{-1,1,-1},{1,-1,-1},{-1,-1,-1} };

	Contact* contact = data->NewContact();
	for (int i = 0; i < 8; i++) {

		//Calculer position de chaque sommet
		Vector3D posVertex = Vector3D(mults[i][0], mults[i][1], mults[i][2]);
		posVertex = posVertex.Product(box.halfsize);
		Matrix4 transform = box.GetTransform();
		posVertex = transform * posVertex;

		float distanceVertex = posVertex.ScalarProduct(plane.normal);

		if (distanceVertex <= plane.offset) {
			contact->contactPoint = plane.normal;
			contact->contactPoint *= (distanceVertex-plane.offset);
			contact->contactPoint += posVertex;
			contact->contactNormal = plane.normal;
			contact->penetration = plane.offset - distanceVertex;
			std::cout << "CONTACT : Point:" << contact->contactPoint.ToString() << "Normal:" << contact->contactNormal.ToString()
				<< "|Penetration:" << contact->penetration << std::endl;
		}
	}

	int nbContacts = data->contacts.size();
	if (nbContacts > 0)
		std::cout << "NBCONTACTS : " << nbContacts << std::endl;
	return data->contacts.size(); //Nombre de collisions détectées
}
