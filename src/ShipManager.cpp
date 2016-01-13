//
//
//
//
//

#include "ShipManager.h"


void Ship::Tick()
{
	if (m_DistanceToDestination < 1)
	{
		m_pPreviousPlanet = m_pDestination;
		if (m_Route.size() > 1)
		{
			m_pDestination = m_Route[0].pDestination->GetDataRef();
			m_DistanceToDestination = m_Route[0].Cost;
			m_Route.erase(m_Route.begin());
		}
	}
	else
	{
		m_DistanceToDestination -= 1;
	}

	if (m_pDestination == m_pPreviousPlanet) // We are currently stationed at a planet
	{
		// Trade code goes here.

	}
}

Ship::Ship()
{
}

Ship::~Ship()
{
}

void ShipManager::Tick()
{

}

ShipManager::ShipManager()
{
	
}


ShipManager::~ShipManager()
{
}
