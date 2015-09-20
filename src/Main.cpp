//
//
//
//
//


#include <iostream>

#include "Main.h"
#include "StateFactory.h"
#include "Timer.h"
#include "Util.h"

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

	GRAPH_DESC Desc = { 1000, 1000, 5, 900 };
	g_pGraphManager = new GraphManager<Planet>(Desc);
	g_pPlanetManager = new PlanetManager();

	std::vector<Planet*> path = g_pGraphManager->ShortestPath_Dijkstra(g_pPlanetManager->GetPlanets()[0], g_pPlanetManager->GetPlanets()[28]);

	for (auto i : path)
	{
		std::cout << i->GetID() << std::endl;
	}

	std::ofstream mapfile;
	mapfile.open("map.txt");

	std::cout << GenerateMapString(&g_pGraphManager->GetGraphData()) << std::endl;
	mapfile << GenerateMapString(&g_pGraphManager->GetGraphData()) << std::endl;
	
	mapfile.close();

	return 0;
}


