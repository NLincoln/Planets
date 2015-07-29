//
//
//
//
//
#pragma once

#include <string>
#include <vector>

typedef unsigned int uint;

template <typename T>
uint GetElementPositionInVector(T Element, std::vector<T> arr)
{
	for (uint i = 0; i < arr.size(); i++)
	{
		if (arr[i] == Element) return i;
	}
}


extern std::vector<std::string> ParseStringIntoArray(std::string string, char pch);