#pragma once
#include <string>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utility/Logger.h"


class Shader
{
private:
	unsigned int id;

public:
	Shader(const std::string& name);
	~Shader();

	void Bind() const;
	void Unbind() const;

	int GetUniformLocation(const std::string& name) const;

	template<typename T>
	void SetUniform(const std::string& name, const T& value)
	{
		std::string message = std::string("Type '") + typeid(T).name() + "' is not supported";
		Logger::Log(Error, message);
		throw std::invalid_argument(message);
	}

	template<>
	void SetUniform(const std::string& name, const glm::vec4& value)
	{
		int location = GetUniformLocation(name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	template<>
	void SetUniform(const std::string& name, const glm::mat4& value)
	{
		int location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
};

