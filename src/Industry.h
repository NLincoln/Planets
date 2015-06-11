//
//
//
//
//

#pragma once

#include <string>
#include "Ore_Stockpile.h"
#include "Main.h"

typedef std::string Ore;

// There is a fundamental difference between a factory and a Refinery
// Factories produce (only ships) from REFINED ore. Refinery's produce that refined ore.
// Factories will make ships based upon a "special mixture" of ores that is specific
//  To that factory.
// Refinery's can only refine so much ore in a single tick. This is going to be
//  a configurable value.
// Refinery's could possibly have efficiency levels? They would upgrade after
//  Processing a certain measure of ore.
// Should we have a cap on stockpile size?
// Should we have one refinery refine multiple ores in a tick? --Yes
typedef unsigned int uint;
class Refinery 
{
	Ore_Map m_RefinedStockpile;
	Ore_Map m_RawStockpile;
	const uint m_RefineRate;
public:
	void Tick();
	void ReceiveRawOre(Ore type, uint amount);
	bool GiveRefinedOre(Ore type, uint amount);
	Refinery();
	~Refinery();
};

class Ship_Maker
{
	Ore_Map m_Recipe;
	uint m_Price;
	void GenerateRecipe();
public:
	Ore_Map GetRecipe()
	{
		return m_Recipe;
	}
	uint GetPrice();

	Ship_Maker();
	~Ship_Maker();
	
};

