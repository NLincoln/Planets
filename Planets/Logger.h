//
//
//
//
//
#pragma once
#include <string>
#include <fstream>
#define FILENAME "Planets.log"

class Logger
{
public:
	Logger();
	~Logger();
	static void Log(std::string message);
	static void ClearLog();
};

