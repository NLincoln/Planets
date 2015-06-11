//
//
//
//
//


#include "Industry.h"

void Refinery::Tick()
{
	//Check if there's enough ore in the stockpile to refine
	if (m_RawStockpile.GetTotalAmount() > m_RefineRate)
	{
 		uint amount = 0;
 		uint total = m_RawStockpile.GetTotalAmount();
 		for (uint i = 0; i < m_RawStockpile.GetOreList().size(); ++i)
 		{
 			amount = (m_RawStockpile.GetOreAmount(m_RawStockpile.GetOreList()[i]) / total) * m_RefineRate;
 			m_RawStockpile.RemoveOreAmount(m_RawStockpile.GetOreList()[i], amount);
 			m_RefinedStockpile.AddOreAmount(m_RawStockpile.GetOreList()[i], amount);
 		}
	}
	else // Refine it all!!!
	{
		std::vector<Ore> list = m_RawStockpile.GetOreList();
		for (uint i = 0; i < list.size(); ++i)
		{
			m_RefinedStockpile.AddOreAmount(list[i], m_RawStockpile.GetOreAmount(list[i]));
			m_RawStockpile.RemoveOre(list[i]);
		}
	}
}

void Refinery::ReceiveRawOre(Ore type, uint amount)
{
	if(IsInVector(type, m_RawStockpile.GetOreList()))
		m_RawStockpile.AddOreAmount(type, amount);
	else
		m_RawStockpile.AddOre(type, amount);
	
}

bool Refinery::GiveRefinedOre(Ore type, uint amount)
{
	if (m_RefinedStockpile.GetOreAmount(type) > amount)
	{
		m_RefinedStockpile.RemoveOreAmount(type, amount);
		return true;
	}
	else return false;
}

Refinery::Refinery() : m_RefineRate(30)
{

}

Refinery::~Refinery()
{
	
}

void Ship_Maker::GenerateRecipe()
{
	//Random selection of ores.
	//Decide how many ores there will be.
	//This number is between 2 and 4
	uint NumOres = Rand::GetRandomUINT(2, 4);
	OreNameGenerator NameGen;
	std::vector<Ore> ores = NameGen.GetMasterOreList();
	for (uint i = 0; i < NumOres; ++i)
	{
		uint index = Rand::GetRandomUINT(0, ores.size());
		m_Recipe.AddOre(ores[index], Rand::GetRandomUINT(4, 15));
		ores.erase(ores.begin() + index);
	}
}

uint Ship_Maker::GetPrice()
{
	return m_Price;
}

Ship_Maker::Ship_Maker()
{
	GenerateRecipe();
}

Ship_Maker::~Ship_Maker()
{

}

