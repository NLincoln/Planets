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

class Planet;
struct Planet_Edge
{
	Planet* pDestination;
	double Cost;
};

struct Point
{
	uint x;
	uint y;
};


class GraphData
{
	Planet* m_pPlanet;
	Point m_Position;
	std::vector<Planet_Edge> m_Neighbors;
public:
	void AddNeighbor(Planet* _new, double _cost);
	Planet_Edge GetNeighborEdge(uint _Index);
	std::vector<Planet_Edge> GetAllNeighbors();
	double GetNeighborTravelCost(uint _Index);
	Planet* GetNeighborPlanet(uint _Index);
	void SetPosition(Point _point);
	
	uint GetNumNeighbors();
	explicit GraphData(Planet* _ptr);
	~GraphData();
};

typedef std::list<GraphData*> Path;

class PlanetManager
{
	std::vector<GraphData*> m_GraphData;
	std::vector<Planet*> m_PlanetList;
	
	Path FindPathBetweenNodes(GraphData* Start, GraphData* End);

	void Create_Universe();
public:
	void Tick();

	Path FindPath(Planet* Start, Planet* End);
	uint GetNumPlanets();
	PlanetManager();
	~PlanetManager();
};
