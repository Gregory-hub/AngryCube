#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Scene.h"
#include "Shader.h"


class Renderer
{
private:
	GLFWwindow* window;
	glm::mat4 projMatrix;

public:
	Renderer(GLFWwindow* w, glm::vec2 resolution);
	void Render(const Scene& scene, Shader& shader) const;
};

