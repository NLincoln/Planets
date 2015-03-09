//
//
//
//
//
#include "Main.hpp"
#include "PlanetManager.hpp"
#include <iostream>
uint Rand::GetRandomUINT(uint min, uint max)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<uint> uni(min, max);
	return uni(rng);
	
}

void LogToFile(std::string message)
{
	
}

int main(int argc, const char** argv)
{
	PlanetManager PlanetManager;
	std::cout << PlanetManager.GetNumPlanets() << std::endl;


	return 0;
}
