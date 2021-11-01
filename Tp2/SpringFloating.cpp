#include "SpringFloating.h"

//apply hooke's law from particles position
void SpringFloating::UpdateForce(Particule* particle, float duration)
{
	float d = particle->position.y;

	if (d >= m_waterHeight - m_maxDepth) return;

	if (d <= m_waterHeight - m_maxDepth)
	{
		Vector3D inc = Vector3D(0, m_liquidDensity * m_volume, 0);
		particle->addForce(inc);
		return;
	}
	
	Vector3D inc = Vector3D(0, (m_liquidDensity * m_volume * (d - m_maxDepth - m_waterHeight)) / (2 * m_maxDepth), 0);
	particle->addForce(inc);
}