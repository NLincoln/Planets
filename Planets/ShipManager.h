//
//
//
//
//
#pragma once

#include "Main.hpp"
#include "Ore_Stockpile.hpp"
#include "PlanetManager.hpp"
// Should Pilots be integrated? Nah. Let's keep it simple

class Ship
{
	uint m_Money;
	
	Ore_Map m_CargoBay;
	uint m_CargoBayLimit;

	Planet* m_pDestination;
	
	Path m_Route;

public:
	Ship();
	~Ship();

};


class ShipManager
{
	std::vector<Ship>
public:
	ShipManager();
	~ShipManager();
};

