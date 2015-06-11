//
//
//
//
//
#pragma once
#include <vector>
#include <string>

class GraphData;
class Planet;

extern void GenerateMapString(std::vector<GraphData*>* Data, std::string* String);
extern std::string GenerateMapString(std::vector<GraphData*>* Data);
extern void GenerateStateString(std::vector<Planet*>* Data, std::string* String);
extern std::string GenerateStateString(std::vector<Planet*>* Data);