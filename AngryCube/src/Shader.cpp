#include "Shader.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <GL/glew.h>

#include "Vector.h"


std::string readFile(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Warning: file not open (" << filename << ")" << std::endl;
        return "";
    }
    std::stringstream ss;
    ss << file.rdbuf();
    file.close();
    return ss.str();
}


Shader::Shader()
{
    std::string vertShaderStr = readFile("shaders/basicColor.vert");
    std::string fragShaderStr = readFile("shaders/basicColor.frag");

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

void Shader::Bind()
{
    glUseProgram(id);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

template<typename T>
void Shader::SetUniform(std::string name, T value)
{
    
}

template<>
void Shader::SetUniform(std::string name, Vector4<float> value)
{
	int location = glGetUniformLocation(id, name.c_str());
	glUseProgram(id);
	glUniform4f(location, value.X, value.Y, value.Z, value.W);
}

