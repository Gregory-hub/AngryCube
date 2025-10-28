#pragma once
#include "pch.h"

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Logger.h"


inline void APIENTRY glDebugOutput(
	GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const char* message,
    const void* userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::string output = std::to_string(id) + ": " + message;

    switch (source)
    {
	case GL_DEBUG_SOURCE_API:				output += " (Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		output += " (Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:	output += " (Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:		output += " (Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:		output += " (Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:				output += " (Source: Other"; break;
    }

    switch (type)
    {
	case GL_DEBUG_TYPE_ERROR:               output += ", Type: Error)"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: output += ", Type: Deprecated Behaviour)"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  output += ", Type: Undefined Behaviour)"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         output += ", Type: Portability)"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         output += ", Type: Performance)"; break;
	case GL_DEBUG_TYPE_MARKER:              output += ", Type: Marker)"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          output += ", Type: Push Group)"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           output += ", Type: Pop Group)"; break;
	case GL_DEBUG_TYPE_OTHER:               output += ", Type: Other)"; break;
    }

	LogLevel logLevel = LogLevel::Info;
    switch (severity)
    {
	case GL_DEBUG_SEVERITY_HIGH:			logLevel = LogLevel::Error; break;
	case GL_DEBUG_SEVERITY_MEDIUM:			logLevel = LogLevel::Warning; break;
	case GL_DEBUG_SEVERITY_LOW:				logLevel = LogLevel::Warning; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:	logLevel = LogLevel::Info; break;
    }

    Logger::Log(logLevel, output);
}

