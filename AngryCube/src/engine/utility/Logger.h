#pragma once

#include <string>


enum class LogLevel
{
	Info,
	Warning,
	Error
};


class Logger
{
public:
	Logger() = delete;

	static void Log(LogLevel logLevel, std::string message);
};

