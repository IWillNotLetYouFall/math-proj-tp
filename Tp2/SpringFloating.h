#pragma once

#include "ParticleForceGenerator.h"

//Spring for floatability

class SpringFloating : public ParticleForceGenerator
{
	//particle properties
	float m_maxDepth; // s
	float m_volume; // v

	//effect properties
	float m_waterHeight; // yw
	float m_liquidDensity; // p

public:
	SpringFloating(float maxDepth, float volume, float waterHeight, float liquidDensity) : 
		m_maxDepth(maxDepth), m_volume(volume), m_waterHeight(waterHeight), m_liquidDensity(liquidDensity) {};

	//apply buoyancy from particles position
	void UpdateForce(Particule* particle, float duration);
};