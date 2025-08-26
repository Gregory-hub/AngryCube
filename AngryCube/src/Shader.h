#pragma once
#include <string>


class Shader
{
private:
	unsigned int id;

public:
	Shader();
	~Shader();

	template<typename T>
	void SetUniform(std::string name, T value);

	void Bind();
	void Unbind();
};
