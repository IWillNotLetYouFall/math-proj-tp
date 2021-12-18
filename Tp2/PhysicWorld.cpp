#include "PhysicWorld.h"
#include "Octree.h"

PhysicWorld::PhysicWorld(int iterations)
{
	contactResolver = ParticleContactResolver(iterations);
}

void PhysicWorld::AddEntry(RigidBody* rigid, ForceGeneratorBody* force)
{
	registre.addEntry(rigid, force); //Main : Initialiser SpringParticle et fetch PA comme param constr
}

void PhysicWorld::RemoveEntries(RigidBody* rigid)
{
	registre.removeEntries(rigid);
}

void PhysicWorld::AddRigidBody(RigidBody* rigid)
{
	rigidReg.push_back(rigid);
}

void PhysicWorld::RemoveRigidBody(RigidBody* rigid)
{
	for (int i = 0; i < rigidReg.size(); i++)
	{
		if (rigidReg[i] == rigid) {
			rigidReg.erase(rigidReg.begin() + i);
			return;
		}
	}
}

void PhysicWorld::AddContactGenerator(ParticleContactGenerator* contactGen)
{
	if (contactGen != NULL)
		contactsGenerators.push_back(contactGen);
}

void PhysicWorld::StartFrame()
{
	for (RigidBody* rigid : rigidReg)
		rigid->ClearAccumulator();
	//registre.clearRegistry();
}

vector<ParticleContact*> PhysicWorld::GenerateContacts()
{
	vector<ParticleContact*> usedContacts;
	ParticleContact* used;
	for (ParticleContactGenerator* gen : contactsGenerators) {
		used = new ParticleContact();
		if (gen->addContact(used, 1) == 1) {
			usedContacts.push_back(used);
		}
	}
	return usedContacts;
}


void PhysicWorld::RunPhysics(float duration)
{
	//contacts.clear();

	//TODO: G�n�rer forces sur les particules
	registre.UpdateForce(duration);

	//Int�gration sur chacune des particules
	for (RigidBody* rigid : rigidReg)
		rigid->Integrate(duration);

	//BroadPhase
	Octree tree = Octree(coordinates.x / 2, coordinates.y / 2, 0);
	tree.subdivide(halfsize);
	for (RigidBody* rigid : rigidReg)
	{
		Octree treeChild = tree.getChild(tree.getChildIndex(rigid->GetPosition()));
		treeChild.subdivide(halfsize/2);
		Octree treeGrandChild = treeChild.getChild(treeChild.getChildIndex(rigid->GetPosition()));
		if (treeGrandChild.getPosition().y - 75 <= 0) //touches top
		{
			cout << treeGrandChild.getPosition().ToString() << endl;
		}
		else if (treeGrandChild.getPosition().y + 75 >= 600) //touches bottom
		{
			cout << treeGrandChild.getPosition().ToString() << endl;
		}
		else if (treeGrandChild.getPosition().x - 75 <= 0) //touches left
		{
			cout << treeGrandChild.getPosition().ToString() << endl;
		}
		else if (treeGrandChild.getPosition().x + 75 >= 600) //touches right
		{
			cout << treeGrandChild.getPosition().ToString() << endl;
		}
		else if (treeGrandChild.getPosition().z - 75 <= -300) //touches front
		{
			cout << treeGrandChild.getPosition().ToString() << endl;
		}
		else if (treeGrandChild.getPosition().z + 75 >= 300) //touches back
		{
			cout << treeGrandChild.getPosition().ToString() << endl;
		}
	}

	//Gestion des collisions
	//G�n�ration des Contacts
	//contacts = GenerateContacts();

	//R�solution des contacts
	//contactResolver.ResolveContacts(contacts, contacts.size(), duration);
}
