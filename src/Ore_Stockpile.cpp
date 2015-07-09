//
//
//
//
//
#include "Main.h"
#include "Ore_Stockpile.h"

std::vector<Ore> OreNameGenerator::GetMasterOreList()
{
	return m_OreList;
}

OreNameGenerator::OreNameGenerator()
{
	std::vector<Ore> names = 
	{
	#include "orenames.txt" //Oh yes I did lol.
	};

	//Choose the ores we need. Or just take the first few
	for (int i = 0; i < NUM_ORES; ++i)
	{
		m_OreList.push_back(names[i]);
	}
}

OreNameGenerator::~OreNameGenerator()
{

}

uint Ore_Map::GetOreAmount(Ore _ore)
{
	return m_OreMap[_ore];
}

void Ore_Map::SetOreAmount(Ore _ore, uint _amount)
{
	m_OreMap[_ore] = _amount;
}

void Ore_Map::AddOreAmount(Ore _ore, uint _amount)
{
	if(!IsInVector(_ore, m_OreList))
		AddOre(_ore);
	m_OreMap[_ore] += _amount;
}

bool Ore_Map::RemoveOreAmount(Ore _ore, uint _amount)
{
	if (_amount < m_OreMap[_ore]) // Make sure we aren't going to move into a negative value accidentally
	{
		m_OreMap[_ore] -= _amount;
		return true;
	}
	else return false; //Unsuccessful.
}

void Ore_Map::AddOre(Ore _ore, uint _amount)
{
	if(!IsInVector(_ore, m_OreList))
	{
		m_OreMap.insert(std::pair<Ore, uint>(_ore, _amount));
		m_OreList.push_back(_ore);
	}
}

void Ore_Map::RemoveOre(Ore _ore)
{
	m_OreMap.erase(_ore);	
}

std::vector<std::string> Ore_Map::GetOreList()
{
	return m_OreList;
}

uint Ore_Map::GetTotalAmount()
{
	uint amount = 0;
	//Iterate through al of the ores in the map and then add up their values.
	for(uint i = 0; i < m_OreList.size(); i++)
	{
		amount += m_OreMap[m_OreList[i]];
	}
	return amount;
}

void Ore_Map::CreateState(std::string* State)
{
	for (uint i = 0; i < m_OreList.size(); ++i)
	{
		State->append(m_OreList[i]);
		State->append(",");
		State->append(std::to_string(m_OreMap[m_OreList[i]]));
		State->append(";");
	}
}

Ore_Map::Ore_Map()
{

}

Ore_Map::~Ore_Map()
{
	
}
