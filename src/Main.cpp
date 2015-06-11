//
//
//
//
//

#include "Main.h"

PlanetManager* g_pPlanetManager;
uint Rand::GetRandomUINT(uint min, uint max)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<uint> uni(min, max);
	return uni(rng);
	
}

float Rand::GetRandomFloat(float min, float max)
{
	float range = max - min;
	float temp = (float)GetRandomUINT(0, UINT_MAX);
	return (temp / UINT_MAX) + min + range;
}

int main(int argc, const char** argv)
{
	Logger::ClearLog();
	g_pPlanetManager = new PlanetManager();

	// I'm bored. Let's actually do that testing thing. 

	return 0;
}
