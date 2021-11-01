#include "ParticleContactResolver.h"

ParticleContactResolver::ParticleContactResolver(unsigned int iterations)
{
	this->iterations = iterations;
}

void ParticleContactResolver::ResolveContacts(std::vector<ParticleContact*> &contactArray, unsigned int numContact, float duration)
{
	int nbMaxContacts = numContact * iterations;
	for (int i = 0; i < nbMaxContacts; i++)
	{
		//Loop Toutes les vel relatives contacts
		float minIndex = 0;
		float minRelative = contactArray[minIndex]->CalculateSeparatingVelocity();
		float currRelative;
		for (int n = 1; n < contactArray.size(); n++)
		{
			currRelative = contactArray[n]->CalculateSeparatingVelocity();
			if (currRelative < minRelative)
				minRelative = currRelative;
		}
		//Si min est > 0, alors break fin loopResolve
		if (minRelative > 0)
			break;

		//Sinon, Resolve et loop
		contactArray[minIndex]->Resolve(duration);
	}
}