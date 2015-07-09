//
//
//
//
//
#pragma once
#include <vector>
#include <string>

template <typename T>
class GraphData;

class Planet;

extern void GenerateMapString(std::vector<GraphData<Planet>*>* Data, std::string* String);
extern std::string GenerateMapString(std::vector<GraphData<Planet>*>* Data);
extern void GenerateStateString(std::vector<Planet*>* Data, std::string* String);
extern std::string GenerateStateString(std::vector<Planet*>* Data);
