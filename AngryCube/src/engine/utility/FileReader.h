#pragma once
#include <string>


class FileReader
{
public:
	FileReader() = delete;

	static std::string ReadFile(const std::string& filename);
};
