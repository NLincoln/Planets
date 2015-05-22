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