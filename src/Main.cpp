//
//
//
//
//

#include <iostream>

#include "Main.h"
#include "StateFactory.h"
#include "Timer.h"

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
	Timer t;
	for (uint i = 0; i < 3; ++i)
	{
		t.start();
		GRAPH_DESC Desc = { 1000, 1000, 5, 750 };
		g_pGraphManager = new GraphManager<Planet>(Desc);

		g_pPlanetManager = new PlanetManager();
		t.stop();
		std::cout << t.getElapsedTimeInSec() << std::endl;

	}
	std::cout << GenerateMapString(&g_pGraphManager->GetGraphData()) << std::endl;
	return 0;
}
