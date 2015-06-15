//
//
//
//
//
#pragma once
#include "Ore_Stockpile.h"
#include "Industry.h"

typedef std::string Ore;

class Planet
{
private:
	uint m_Money;
	uint m_id;
	uint m_Population;
	
	float m_PopulationModifier;

	Ore_Map m_RawStockpile;
	Ore_Map m_RefinedStockpile;
	Ore_Map m_Prices;
	
	Ship_Maker m_Factory;
	Refinery m_Refinery;

	void UpdatePrices();
	void UpdatePopulation();
	
public:
	//Sell ore to the planet
	//returns the amount the planet is paying
	uint SellOre(Ore _ore, uint _amount);
	uint GetOrePrice(Ore _ore);

	void CreateState(std::string* Out);
	
	void Tick();	
	uint GetID()
	{
		return m_id;
	}
	Planet(uint _id);
	~Planet();
};

