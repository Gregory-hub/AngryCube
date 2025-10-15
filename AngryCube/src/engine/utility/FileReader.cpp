#include "FileReader.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include "Logger.h"


std::string FileReader::ReadFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		Logger::Log(Warning, std::string("file not open (") + filename + ")");
		return "";
	}
	std::stringstream ss;
	ss << file.rdbuf();
	file.close();
	return ss.str();
}
