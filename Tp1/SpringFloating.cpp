#include "SpringFloating.h"

//apply hooke's law from particles position
void SpringFloating::UpdateForce(Particule* particle, float duration)
{
	float d = (particle->position.y - m_waterHeight - m_maxDepth) / (2 * m_maxDepth);
	float inc;

	if (d >= 1)
	{
		inc = m_volume * m_liquidDensity;
		particle->velocite += inc * duration;
	}
	else if (d > 0)
	{
		inc = d * m_volume * m_liquidDensity;
		particle->velocite += inc * duration;
	}
}