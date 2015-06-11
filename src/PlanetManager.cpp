//
//
//
//
//
#include <map>

#include "Main.hpp"
#include "PlanetManager.hpp"
#include "GraphManager.h"
#include "Planet.hpp"
#include "Path.hpp"


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
	ASSERT(m_PlanetList.size() == NUM_PLANETS);
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
}

GraphManager PlanetManager::GetGraphData()
{
	return m_GraphData;
}

uint PlanetManager::GetNumPlanets()
{
	return m_PlanetList.size();
}

void PlanetManager::AddOccupiedEdge(std::tuple < Ship*, Planet*, Planet*> Edge)
{
	m_OccupiedEdges.push_back(Edge);
}

void PlanetManager::AddOccupiedEdge(Ship* Ship, Planet* Planet1, Planet* Planet2)
{
	AddOccupiedEdge(std::make_tuple(Ship, Planet1, Planet2));
}

void PlanetManager::AddOccupiedEdge(Ship* Ship, std::pair < Planet*, Planet*> Planets)
{
	AddOccupiedEdge(std::make_tuple(Ship, Planets.first, Planets.second));
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
