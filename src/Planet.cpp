//
//
//
//
//

#include <string>

#include "Planet.hpp"
#include "Ore_Stockpile.hpp"

void Planet::UpdatePrices()
{
	// I still have no idea how to do these.
		
}

void Planet::UpdatePopulation()
{
	//TODO: this
	
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
	m_Stockpile.AddOreAmount(_ore, _amount);
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
	m_Stockpile.CreateState(&MapStr);
	Out->append(MapStr);
	Out->append("},{");
	m_Prices.CreateState(&MapStr);
	Out->append(MapStr);
	Out->append("};\n");
}

void Planet::Tick()
{
	//TODO: this
	UpdatePopulation();
	UpdatePrices();
}

void RandomlyGenerate()
{
	//TODO: this
}

Planet::Planet(uint _id)
{
	m_id = _id;
	m_Money = Rand::GetRandomUINT(500, 10000);
	m_Population = Rand::GetRandomUINT(10, 5000);
}


Planet::~Planet()
{
	
}
