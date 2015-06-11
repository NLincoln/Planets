//
//
//
//
//

class Ship;

class Factory
{
    Ore_Map m_Recipe;
    uint m_Price;
public:
	Ore_Map GetRecipe()
	{
		return m_Recipe;
	}
	Ship* CreateShip();
};
