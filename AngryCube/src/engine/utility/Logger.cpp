#include "pch.h"
#include "Logger.h"

#include <iostream>


void Logger::Log(LogLevel logLevel, std::string message)
{
	switch (logLevel)
	{
	case LogLevel::Info:
		std::cout << "[Info] ";
		break;
	case LogLevel::Warning:
		std::cout << "[Warning] ";
		break;
	case LogLevel::Error:
		std::cout << "[Error] ";
		break;
	}

	std::cout << message << '\n' << std::flush;
}
