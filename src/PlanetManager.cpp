//
//
//
//
//
#include <map>

#include "Main.h"
#include "PlanetManager.h"
#include "GraphManager.h"
#include "Planet.h"
#include "Path.h"


uint square(uint x)
{
	return x * x;
}

uint DistanceSquared(Point a, Point b) 
{
	return square(a.x - b.x) + square(a.y - b.y);
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
	for (uint i = 0; i < NUM_PLANETS; ++i)
	{
		m_GraphData.Add_Node(m_PlanetList[i]);
	}
	m_GraphData.Create_Graph();
}

void PlanetManager::Tick()
{
	for (uint i = 0; i < m_PlanetList.size(); i++)
	{
		m_PlanetList[i]->Tick();
	}
	// Next we need to iterate across all of the ships.

}

GraphManager PlanetManager::GetGraphData()
{
	return m_GraphData;
}

uint PlanetManager::GetNumPlanets()
{
	return (uint)m_PlanetList.size();
}

std::vector<Ship*> PlanetManager::QueryOccupiedEdge(std::pair<Planet*, Planet*> Key)
{
	std::vector<Ship*> Out;
	if (Key.first == Key.second)
		return Out;
	for (uint i = 0; i < m_OccupiedEdges.size(); ++i)
	{
		auto t = m_OccupiedEdges[i];
		if ((std::get<1>(t) == Key.first || std::get<1>(t) == Key.second) && (std::get<2>(t) == Key.first || std::get<2>(t) == Key.second))
		{
			Out.push_back(std::get<0>(t));
		}
	}
	return Out;
}

PlanetManager::PlanetManager()
{
	//Initialize the list of planets.
	for (uint i = 0; i < NUM_PLANETS; ++i)
	{
		Planet* t = new Planet(i);
		m_PlanetList.push_back(t);
	}
	Create_Universe();
}


PlanetManager::~PlanetManager()
{
	for (uint i = 0; i < m_PlanetList.size(); i++)
	{
		delete m_PlanetList[i];
		delete m_GraphData->at(i);
	}
}
