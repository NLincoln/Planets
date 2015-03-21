//
//
//
//
//
#include "Main.hpp"
#include "PlanetManager.hpp"
#include "Logger.h"
#include <iostream>
uint Rand::GetRandomUINT(uint min, uint max)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<uint> uni(min, max);
	return uni(rng);
	
}

int main(int argc, const char** argv)
{
	Logger::ClearLog();
	PlanetManager PlanetManager;
	return 0;
}
