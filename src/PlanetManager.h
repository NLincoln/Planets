//
//
//
//
//
#pragma once
#include <list>
#include "GraphManager.h"

class Ship;
typedef std::list<GraphData*> Path;
typedef unsigned int uint;
struct Point;


uint square(uint x);
uint DistanceSquared(Point a, Point b);

class PlanetManager
{
	// This is turning into a god class. Not good.
	GraphManager m_GraphData;
	std::vector<Planet*> m_PlanetList;
	
	Path FindPathBetweenNodes(GraphData* Start, GraphData* End);

	void Create_Universe();
	
	std::vector<std::tuple<Ship*, Planet*, Planet*>> m_OccupiedEdges;

public:
	void Tick();

	GraphManager GetGraphData();
	uint GetNumPlanets();

	void AddOccupiedEdge(std::tuple<Ship*, Planet*, Planet*> Edge);
	void AddOccupiedEdge(Ship* Ship, Planet* Planet1, Planet* Planet2);
	void AddOccupiedEdge(Ship* Ship, std::pair<Planet*, Planet*> Planets);
	
	std::vector<Ship*> QueryOccupiedEdge(std::pair<Planet*, Planet*> Key);

	PlanetManager();
	~PlanetManager();
};
