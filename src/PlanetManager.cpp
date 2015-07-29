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
#include "ShipManager.h"

uint square(uint x)
{
	return x * x;
}

uint DistanceSquared(Point a, Point b) 
{
	return square(a.x - b.x) + square(a.y - b.y);
}


void PlanetManager::Create_Universe()
{
	//Double check that the planet list is initialized
	for (uint i = 0; i < NUM_PLANETS; ++i)
	{
		g_pGraphManager->Add_Node(m_PlanetList[i]);
	}
	g_pGraphManager->Create_Graph();
}

void PlanetManager::Tick()
{
	for (uint i = 0; i < m_PlanetList.size(); i++)
	{
		m_PlanetList[i]->Tick();
	}
	// Next we need to iterate across all of the ships.
	 
	// The way this works is we clear the vector containing the ship location data and refill it each time.
	// Although there's definitely a better way... This way is easier and doesn't require the ships to be aware of the planetmanager.
	
	m_OccupiedEdges.clear();

	for (uint i = 0; i < m_Ships.size(); ++i)
	{
		std::tuple<Ship*, Planet*, Planet*> t;
		Ship* s = m_Ships[i];
		if (s->m_pDestination == NULL)
		{
			continue;
		}
		std::get<0>(t) = s;
		std::get<1>(t) = s->m_pDestination;
		std::get<2>(t) = s->m_pPreviousPlanet;
		m_OccupiedEdges.push_back(t);
	}
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
	}
}
