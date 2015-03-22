//
//
//
//
//
#pragma once

#include <vector>
#include <list>

#include "Main.hpp"
class Planet;
class GraphData;
typedef std::list<GraphData*> Path;


struct Graph_Edge
{
	GraphData* pDestination;
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
	std::vector<Graph_Edge> m_Neighbors;
public:
	void						AddNeighbor(GraphData* _new, double _cost);
	Graph_Edge					GetNeighborEdge(uint _Index);
	std::vector<Graph_Edge>		GetAllNeighbors();
	double						GetNeighborTravelCost(uint _Index);
	GraphData*					GetNeighborPlanet(uint _Index);
	void						SetPosition(Point _point);
	uint						GetNumNeighbors();

	explicit GraphData(Planet* _ptr);
	~GraphData();
};

class GraphManager
{	
	std::vector<GraphData*> m_GraphData;
	void Verify_Graph();
public:
	std::vector<GraphData*>* operator-> ()
	{
		return &m_GraphData;
	}
	Path FindPath(GraphData* Start, GraphData* End);
	uint GetNumNodes()
	{
		return m_GraphData.size();
	}
	void Create_Graph();
	void Add_Node(Planet* Node);
	GraphManager();
	~GraphManager();
};
