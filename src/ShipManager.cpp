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
			m_pDestination = m_Route.front()->GetDataRef();
			m_DistanceToDestination = m_Route.front()->GetNeighborTravelCost(m_pPreviousPlanet);
		}
		else // End of route, we are at our final destination!
		{

		}
	}
	else
	{
		m_DistanceToDestination -= 1;
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
