//
//
//
//
//
#pragma once

#include <vector>
#include <set>
#include <list>
#include "Planet.hpp"
#include "GraphManager.h"


uint square(uint x);
uint DistanceSquared(Point a, Point b);


class PlanetManager
{
	GraphManager m_GraphData;
	std::vector<Planet*> m_PlanetList;
	
	Path FindPathBetweenNodes(GraphData* Start, GraphData* End);

	void Create_Universe();
public:
	void Tick();

	uint GetNumPlanets();
	PlanetManager();
	~PlanetManager();
};
