//
//
//
//
//
#pragma once
#include "Ore_Stockpile.hpp"
#include "Factory.h"

typedef std::string Ore;

class Planet
{
private:
	uint m_Money;
	uint m_id;
	uint m_Population;
	
	float m_PopulationModifier;

	Ore_Map m_Stockpile;
	Ore_Map m_Prices;
	
	Factory m_Factory;

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

