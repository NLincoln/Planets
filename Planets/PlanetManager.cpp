//
//
//
//
//
#include <queue>
#include <map>

#include "Path.hpp"
#include "PlanetManager.hpp"
#include "Main.hpp"


uint square(uint x)
{
	return x * x;
}

uint DistanceSquared(Point a, Point b) 
{
	return square(a.x - b.x) + square(a.y - b.y);
}

void GraphData::AddNeighbor(Planet* _new, double _cost)
{
	//Double check that the new planet isn't already a neighbor:
	for (auto it = m_Neighbors.begin(); it != m_Neighbors.end(); it++)
	{
		if (_new == it->pDestination)//Not a new planet
			return;
	}
	Planet_Edge t;
	t.Cost = _cost;
	t.pDestination = _new;
	m_Neighbors.push_back(t);
}

Planet_Edge GraphData::GetNeighborEdge(uint _index)
{
	return m_Neighbors[_index];
}

std::vector<Planet_Edge> GraphData::GetAllNeighbors()
{
	return m_Neighbors; //Hate doing this, has to be done.
}

double GraphData::GetNeighborTravelCost(uint _index)
{
	return m_Neighbors[_index].Cost;
}

Planet* GraphData::GetNeighborPlanet(uint _index)
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

template <typename T>
uint GetElementPositionInVector(T Element, std::vector<T> arr)
{
	for (uint i = 0; i < arr.size(); i++)
	{
		if (arr[i] == Element) return i;
	}
}

Path PlanetManager::FindPathBetweenNodes(GraphData* Start, GraphData* End)
{
	ShortestPath<GraphData*> PathData;
	std::multimap<GraphData*, GraphData*> Edges;
	Path Path;
	
	uint length = PathData.Resolve(Edges, Start, End, Path);
	return Path;
}

void PlanetManager::Create_Universe()
{
	//Double check that the planet list is initialized
	ASSERT(m_PlanetList.size() == NUM_PLANETS);

	std::vector<Point> Points;
	for (auto it = m_PlanetList.begin(); it != m_PlanetList.end(); it++) 
	{
		uint counter = 0;
	beginning: //I want to cry
		Point t;
		t.x = Rand::GetRandomUINT(0, FIELD_WIDTH);
		t.y = Rand::GetRandomUINT(0, FIELD_HEIGHT);
		//Double check for duplicates:
		for (uint i = 0; i < Points.size(); i++)
		{
			if (Points[i].x == t.x && Points[i].y == t.y)
				goto beginning; //I just died a tiny bit. 
		}
		
		//Point is unique, add it.
		Points.push_back(t);
		m_GraphData[counter++]->SetPosition(t);
	}
	for (uint i = 0; i < Points.size(); i++)
	{
		uint NumConnections = 0;
		uint Radius = 5;
		while (NumConnections < MIN_NUM_NEIGHBORS)
		{
			for (uint j = 0; j < Points.size(); j++)
			{
				uint Distance = DistanceSquared(Points[i], Points[j]);
				if (Distance < square(Radius))
				{
					m_GraphData[i]->AddNeighbor(m_PlanetList[j], std::sqrt(Distance));
					m_GraphData[j]->AddNeighbor(m_PlanetList[i], std::sqrt(Distance));
				}
			}
			++Radius;
		}
	}
}

void PlanetManager::Tick()
{
	for (uint i = 0; i < m_PlanetList.size(); i++)
	{
		m_PlanetList[i]->Tick();
	}
}

uint PlanetManager::GetNumPlanets()
{
	return m_PlanetList.size();
}

PlanetManager::PlanetManager()
{
	//Initialize the list of planets.
	for (size_t i = 0; i < NUM_PLANETS; i++)
	{
		Planet* t = new Planet(i);
		m_PlanetList.push_back(t);
		GraphData* a = new GraphData(t);
		m_GraphData.push_back(a);
	}
	Create_Universe();
}


PlanetManager::~PlanetManager()
{
	for (uint i = 0; i < m_PlanetList.size(); i++)
	{
		delete m_PlanetList[i];
		delete m_GraphData[i];
	}
}
