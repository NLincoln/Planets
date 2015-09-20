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
	auto it = std::find(arr.begin(), arr.end(), Element);
	
	uint out = it - arr.begin();
	if (arr[out] == Element)
		return out;
	else return 0;
}

namespace Set
{
	template <typename T>
	std::vector<T> Union(std::vector<T> A, std::vector<T> B) // List of unique elements that are in either A or B
	{
		std::vector<T> Out;
		Out.insert(Out.begin(), A.begin(), A.end()); 
		for (uint i = 0; i < B.size(); ++i)
			if (!Set::ElementOf(B[i], Out))
				Out.push_back(B[i]);
		return Out;
	}

	template <typename T>
	std::vector<T> Intersect(std::vector<T> A, std::vector<T> B) // List of elements that are in both A and B
	{
		std::vector<T> Out;
		for (uint i = 0; i < A.size(); ++i)
			if (Set::ElementOf(A[i], B))
				Out.push_back(A[i]);
		return Out;
	}

	template <typename T>
	bool Subset(std::vector<T> MainSet, std::vector<T> SubSet) 
	{
		for (uint i = 0; i < SubSet.size(); ++i)
			if (!Set::ElementOf(SubSet[i], MainSet))
				return false;
		return true;
	}

	template <typename T>
	bool ElementOf(T Element, std::vector<T> Set)
	{
		if (Set.size() == 0)
			return false;
		for (auto elem : Set)
			if (elem == Element)
				return true;
		return false;
	}

}
extern std::vector<std::string> ParseStringIntoArray(std::string string, char pch);
