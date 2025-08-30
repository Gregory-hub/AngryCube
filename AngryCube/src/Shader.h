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
	void SetUniform(const std::string& name, const T& value);

	void Bind();
	void Unbind();
};

