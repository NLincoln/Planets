//
//
//
//
//

#pragma once
#include <random>
#include <string>
#include <fstream>
typedef unsigned int uint;

#define FIELD_HEIGHT 1000
#define FIELD_WIDTH  1000
#define NUM_PLANETS  750
#define MIN_NUM_NEIGHBORS 5

#define ASSERT(expression) \
	if(!expression) \
		{ \
		LogToFile("ASSERTION FAILED:" #expression);	\
	}

namespace Rand
{
	uint GetRandomUINT(uint min, uint max);
}

template<typename T>
bool IsInVector(T item, std::vector<T> vector)
{
	if(std::find(vector.begin(), vector.end(), item)!=vector.end())
		return true;
	else return false;
}

extern void LogToFile(std::string message);