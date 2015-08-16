//
//
//
//
//

#pragma once
#include <random>
#include "Logger.h"
#include "PlanetManager.h"


typedef unsigned int uint;

#define NUM_PLANETS  750

#define ASSERT(expression)								\
	if(!expression)										\
	{													\
		Logger::Log("ASSERTION FAILED:" #expression);	\
	}													\
	else												\
	{													\
		Logger::Log("ASSERTION SUCCEEDED:" #expression);\
	}


namespace Rand
{
	uint GetRandomUINT(uint min, uint max);
	float GetRandomFloat(float min, float max);
}

template<typename T>
bool IsInVector(T item, std::vector<T> vector)
{
	return std::find(vector.begin(), vector.end(), item) != vector.end();
}

typedef std::vector<Graph_Edge<Planet>> Path;

extern PlanetManager* g_pPlanetManager;
extern GraphManager<Planet>* g_pGraphManager;