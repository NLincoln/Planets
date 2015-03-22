//
//
//
//
//

#include "GraphManager.h"
#include "PlanetManager.hpp"
#include "Path.hpp"

bool DepthFirst_iter(GraphData* Start, GraphData* End, std::vector<GraphData*>* Searched)
{
	if (Start == NULL)
		return false;
	if (Start == End)
		return true;
	Searched->push_back(Start);
	std::vector<Graph_Edge> Neighbors = Start->GetAllNeighbors();
	for (uint i = 0; i < Neighbors.size(); ++i)
	{
		//Make sure that the node hasn't already been searched.
		if (std::find(Searched->begin(), Searched->end(), Neighbors[i].pDestination) == Searched->end())
			if (DepthFirst_iter(Neighbors[i].pDestination, End, Searched) == true)
				return true;
	}
	return false;
}

bool DepthFirst(GraphData* Start, GraphData* End)
{
	std::vector<GraphData*>* Searched = new std::vector<GraphData*>;
	if (Start == End)
		return true;
	Searched->push_back(Start);
	std::vector<Graph_Edge> Neighbors = Start->GetAllNeighbors();
	for (uint i = 0; i < Neighbors.size(); ++i)
	{
		if (DepthFirst_iter(Neighbors[i].pDestination, End, Searched) == true)
			return true;
	}
	return false;
}

void GraphData::AddNeighbor(GraphData* _new, double _cost)
{
	for (uint i = 0; i < m_Neighbors.size(); ++i)
	{
		if (_new == m_Neighbors[i].pDestination)
			return;
	}
	Graph_Edge t;
	t.Cost = _cost;
	t.pDestination = _new;
	m_Neighbors.push_back(t);
}

Graph_Edge GraphData::GetNeighborEdge(uint _index)
{
	return m_Neighbors[_index];
}

std::vector<Graph_Edge> GraphData::GetAllNeighbors()
{
	return m_Neighbors; 
}

double GraphData::GetNeighborTravelCost(uint _index)
{
	return m_Neighbors[_index].Cost;
}

GraphData* GraphData::GetNeighborPlanet(uint _index)
{
	return m_Neighbors[_index].pDestination;
}

void GraphData::SetPosition(Point _point)
{
	m_Position = _point;
}

uint GraphData::GetNumNeighbors()
{
	return m_Neighbors.size();
}

GraphData::GraphData(Planet* _ptr)
{
	m_pPlanet = _ptr;
}

GraphData::~GraphData()
{

}

void GraphManager::Verify_Graph()
{
	/*
	* Start out by attempting to divide the graph into subgraphs. 
	* Then resolve those subgraphs
	*/
	std::vector<std::vector<GraphData*>> Subgraphs;
	std::vector<GraphData*> sub;
	std::vector<GraphData*> NodesLeft = m_GraphData;
	while (NodesLeft.empty() == false)
	{
		GraphData* t = NodesLeft[0];
		NodesLeft.erase(NodesLeft.begin());
		sub.push_back(t);
		for (uint i = 0; i < NodesLeft.size(); i++)
		{
			
			if (DepthFirst(t, NodesLeft[i]))
			{
				sub.push_back(NodesLeft[i]);
				NodesLeft.erase(NodesLeft.begin() + i);
			}
		}
		Subgraphs.push_back(sub);
		sub.clear();
	}
	//TODO: combine the subgraphs

}

Path GraphManager::FindPath(GraphData* Start, GraphData* End)
{
	ShortestPath<GraphData*> PathData;
	std::multimap<GraphData*, GraphData*> Edges;
	Path Path;
	uint length = PathData.Resolve(Edges, Start, End, Path);
	return Path;
}

void GraphManager::Create_Graph()
{
	//Check that the GraphData list is initialized
	ASSERT(m_GraphData.size() == NUM_PLANETS);
	ASSERT(MIN_NUM_NEIGHBORS <= NUM_PLANETS);
	//I'm really just rewriting PlanetManager::Create_Universe() here
	std::vector<Point> Points;
	for (auto it = m_GraphData.begin(); it != m_GraphData.end(); it++)
	{
		uint counter = 0;
	beginning:
		Point t;
		t.x = Rand::GetRandomUINT(0, FIELD_WIDTH);
		t.y = Rand::GetRandomUINT(0, FIELD_HEIGHT);
		//Make sure it's not a duplicate
		for (uint i = 0; i < Points.size(); ++i)
		{
			if (Points[i].x == t.x && Points[i].y == t.y)
				goto beginning;
		}
		Points.push_back(t);
		m_GraphData[counter++]->SetPosition(t);
	}
	ASSERT(Points.size() == m_GraphData.size());
	for (uint i = 0; i < Points.size(); i++)
	{
		uint Radius = 5;
		while (m_GraphData[i]->GetNumNeighbors() < MIN_NUM_NEIGHBORS)
		{
			for (uint j = 0; j < Points.size(); ++j)
			{
				uint Distance = DistanceSquared(Points[i], Points[j]);
				if (Distance <= square(Radius))
				{
					m_GraphData[i]->AddNeighbor(m_GraphData[j], std::sqrt(Distance));
					m_GraphData[j]->AddNeighbor(m_GraphData[i], std::sqrt(Distance));
				}
			}
			++Radius;
		}
	}
	Verify_Graph();
}

void GraphManager::Add_Node(Planet* Node)
{
	GraphData* t = new GraphData(Node);
	m_GraphData.push_back(t);
}

GraphManager::GraphManager()
{
}


GraphManager::~GraphManager()
{
}
