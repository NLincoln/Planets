//
//
//
//
//
#pragma once
#include <vector>
#include <utility>
#include <list>

#include "Ore_Stockpile.h"

class GraphData;
typedef std::list<GraphData*> Path;
typedef unsigned int uint;
class Planet;

class Ship
{
	uint m_Money;
	
	Ore_Map m_CargoBay;
	uint m_CargoBayLimit;

	Planet* m_pDestination;
	Planet* m_pPreviousPlanet;

	Ore_Map m_Recipe;

	Path m_Route;
	friend class PlanetManager;
public:

	void Tick();

	Ship();
	~Ship();

};


class ShipManager
{
	std::vector<Ship> m_Ships;

public:
	void Tick();

	ShipManager();
	~ShipManager();
};
