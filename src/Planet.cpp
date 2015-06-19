//
//
//
//
//

#include <string>

#include "Planet.h"
#include "Ore_Stockpile.h"

void Planet::UpdatePrices()
{
	// First things first, we really don't care about a resorce if we aren't
	// going to use it. Therefore, those that aren't deemed critical should be 
	// set to 0
	
	// At the moment, the only ores that are needed are those that are those to make the ships in the factory

	std::vector<Ore> NecessaryOres = m_Factory.GetRecipe().GetOreList();

	// Set all the ores that are not in the list to 0;
	for (uint i = 0; i < m_Prices.GetOreList().size(); ++i)
	{
		if (!IsInVector(m_Prices.GetOreList()[i], NecessaryOres))
		{
			uint needed = m_Factory.GetRecipe().GetOreAmount(m_Prices.GetOreList()[i]);
			//The more it is needed, the more we should be willing to pay;
			uint price = needed;
			//Planets with more money should pay more because they have more.
			price = (double)price * (double)m_Money * .7; // That decimal number *may* need to be adjusted
			// However, if a planet has a fuckton of the stuff already... Then just nuke the price 
			price = price / (m_RawStockpile.GetOreAmount(m_Prices.GetOreList()[i]) / 3); // Three here is another number that *may* need to be adjusted
		}
		else
		{
			m_Prices.SetOreAmount(m_Prices.GetOreList()[i], 0);
		}
	}
}

void Planet::UpdatePopulation()
{
	//Planet population is directly based upon their cash reserves, with a few caveats.
	m_Population = m_Money * m_PopulationModifier;
}

uint Planet::SellOre(Ore _ore, uint _amount)
{
	uint Price = m_Prices.GetOreAmount(_ore);
	uint AmountPaid = Price * _amount;
	if (m_Money < AmountPaid)
	{
		// The planet doesn't have enough cash to buy all this ore
		// Return 0.
		// God I really hate doing this, because I know I'm gonna forget to
		//  check for it being 0 and to attempt to retrade.
		// It's times like these that being able to return multiple values 
		//  would be SUPER useful.
		return 0; 
	}
	//We can pay for this!!!
	m_RawStockpile.AddOreAmount(_ore, _amount);
	m_Money -= AmountPaid;
	return AmountPaid;
}

uint Planet::GetOrePrice(Ore _ore)
{
	return m_Prices.GetOreAmount(_ore);
}

void Planet::CreateState(std::string* Out)
{
	Out->append(std::to_string(m_id));
	Out->append(":");
	Out->append(std::to_string(m_Money));
	Out->append(",");
	Out->append(std::to_string(m_Population));
	Out->append(",{");
	std::string MapStr;
	m_RawStockpile.CreateState(&MapStr);
	Out->append(MapStr);
	Out->append("},{");
	m_Prices.CreateState(&MapStr);
	Out->append(MapStr);
	Out->append("};\n");
}

void Planet::Tick()
{
	UpdatePopulation();
	UpdatePrices();
	
	// Transfer all of the ores from the refinery to out refined stockpile
	for (uint i = 0; i < m_Refinery.m_RefinedStockpile.GetOreList().size(); ++i)
	{
		uint amount = 0;
		m_Refinery.GiveRefinedOre(m_Refinery.m_RefinedStockpile.GetOreList()[i], &amount);
		m_RefinedStockpile.AddOreAmount(m_Refinery.m_RefinedStockpile.GetOreList()[i], amount);
	}
	//Transfer all the ores from our raw stockpile to the refinery
	for (uint i = 0; i < m_RawStockpile.GetOreList().size(); ++i)
	{
		uint amount = m_RawStockpile.GetOreAmount(m_RawStockpile.GetOreList()[i]);
		m_Refinery.ReceiveRawOre(m_RawStockpile.GetOreList()[i], amount);
		m_RawStockpile.SetOreAmount(m_RawStockpile.GetOreList()[i], 0);
	}
	// Call Tick() on the refinery
	m_Refinery.Tick();

	// Now we hand all all of the refined ore to m_Factory
	
}

Planet::Planet(uint _id) : m_Factory()
{
	m_id = _id;
	m_Money = Rand::GetRandomUINT(500, 10000);
	m_Population = Rand::GetRandomUINT(10, 5000);
	m_PopulationModifier = Rand::GetRandomFloat(.5, 2);
	UpdatePrices();
	UpdatePopulation();
	
	// Initialize the m_Prices and m_RawStockpile
	for (Ore i : m_Factory.GetRecipe().GetOreList())
	{
		m_Prices.AddOre(i, 0);
		m_RawStockpile.AddOre(i, Rand::GetRandomUINT(20, 100));
	}
}


Planet::~Planet()
{
	
}
