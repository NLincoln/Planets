//
//
//
//
//

#include "Logger.h"

void Logger::Log(std::string message)
{
	std::ofstream file;
	file.open(FILENAME, std::ios::out | std::ios::app);
	file << message << "\n";
}

void Logger::ClearLog()
{
	std::ofstream file;
	file.open(FILENAME, std::ios::out | std::ios::trunc);
	file.close();
}
Logger::Logger()
{
}


Logger::~Logger()
{

}
