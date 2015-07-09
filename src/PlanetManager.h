//
//
//
//
//
#pragma once
#include <list>
#include "GraphManager.h"
#include "Planet.h"

class Planet;
class Ship;
typedef unsigned int uint;
struct Point;

uint square(uint x);
uint DistanceSquared(Point a, Point b);

// This is turning into a god class. Not good.
class PlanetManager
{
	std::vector<Planet*> m_PlanetList;
	
	std::list<GraphData<Planet>*> FindPathBetweenNodes(GraphData<Planet>* Start, GraphData<Planet>* End);

	void Create_Universe();

	std::vector<Ship*> m_Ships;
	std::vector<std::tuple<Ship*, Planet*, Planet*>> m_OccupiedEdges;

public:
	void Tick();

	uint GetNumPlanets();

	std::vector<Ship*> QueryOccupiedEdge(std::pair<Planet*, Planet*> Key);

	PlanetManager();
	~PlanetManager();
};
