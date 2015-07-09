//
//
//
//
//

#include <iostream>

#include "Main.h"
#include "StateFactory.h"


PlanetManager* g_pPlanetManager;
GraphManager<Planet>* g_pGraphManager;
uint Rand::GetRandomUINT(uint min, uint max)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<uint> uni(min, max);
	return uni(rng);
	
}

float Rand::GetRandomFloat(float min, float max)
{
	float range = max - min;
	float temp = (float)GetRandomUINT(0, UINT_MAX);
	return (temp / UINT_MAX) + min + range;
}

int main(int argc, const char** argv)
{
	Logger::ClearLog();

	GRAPH_DESC Desc = { 1000, 1000, 5, 750 };
	g_pGraphManager = new GraphManager<Planet>(Desc);

	g_pPlanetManager = new PlanetManager();

	std::cout << GenerateMapString(&g_pGraphManager->GetGraphData()) << std::endl;
	return 0;
}
