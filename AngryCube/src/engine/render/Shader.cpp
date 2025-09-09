#include "Shader.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/vec4.hpp>
#include "GLBufferManager.h"


std::string readFile(const std::string& filename)
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

Shader::Shader(const std::string& name)
{
    std::string vertShaderStr = readFile(std::string("shaders/") + name + ".vert");
    std::string fragShaderStr = readFile(std::string("shaders/") + name + ".frag");

    id = glCreateProgram();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char* vertShaderSrc = vertShaderStr.c_str();
    glShaderSource(vs, 1, &vertShaderSrc, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragShaderSrc = fragShaderStr.c_str();
    glShaderSource(fs, 1, &fragShaderSrc, nullptr);
    glCompileShader(fs);

    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);
    //glValidateProgram(id);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

void Shader::Bind() const
{
    glUseProgram(id);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name) const
{
	int location = glGetUniformLocation(id, name.c_str());
	if (location == -1)
        Logger::Log(Warning, std::string("uniform '") + name + "' doesn't exist!");
	return location;
}

