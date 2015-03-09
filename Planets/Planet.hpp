//
//
//
//
//
#pragma once
#include <vector>
#include "Main.hpp"
#include "Ore_Stockpile.hpp"


class Planet
{
private:
	uint m_Money;
	uint m_id;
	uint m_Population;
	
	Ore_Map m_Stockpile;
	Ore_Map m_Prices;
	
	void UpdatePrices();
	void UpdatePopulation();
	void RandomlyGenerate();
	
public:
	//Sell ore to the planet
	//returns the amount the planet is paying
	uint SellOre(Ore _ore, uint _amount);
	uint GetOrePrice(Ore _ore);
	
	void Tick();	
	
	Planet(uint _id);
	~Planet();
};

