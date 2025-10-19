#include "pch.h"
#include "Shader.h"

#include <GL/glew.h>

#include "engine/utility/FileReader.h"


Shader::Shader(const std::string& name)
{
    filename = name;

    std::string vertShaderStr = FileReader::ReadFile(std::string("shaders/") + name + ".vert");
    std::string fragShaderStr = FileReader::ReadFile(std::string("shaders/") + name + ".frag");

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
    glValidateProgram(id);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

Shader::Shader(const Shader& other)
    : Shader(other.filename)
{
}

Shader& Shader::operator=(Shader other)
{
    std::swap(this->id, other.id);
    std::swap(this->filename, other.filename);
    return *this;
}

Shader::Shader(Shader&& other) noexcept
{
    id = std::exchange(other.id, 0);
    filename = std::move(other.filename);
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    if (this != &other)
    {
		id = std::exchange(other.id, 0);
        filename = std::move(other.filename);
    }
    return *this;
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
        Logger::Log(LogLevel::Warning, std::string("uniform '") + name + "' doesn't exist!");
	return location;
}

