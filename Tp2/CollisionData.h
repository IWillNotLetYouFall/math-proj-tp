#pragma once
#include "Contact.h"
#include "Vector3D.h"
#include <cmath>
#include <iostream>
#include <string>
#include "Rigidbody.h"

using namespace sf;
using namespace std;

class CollisionData
{
public:
	vector<Contact*> contacts;
	vector<int> test;
	int nombreMaxContacts = 10;

public:
	bool HasContactsLeft() { return contacts.size() < nombreMaxContacts; };
	void Reset() { contacts.clear(); };
	Contact* NewContact() { 
		Contact* newContact = new Contact();
		contacts.push_back(newContact);
		return newContact; };
};

