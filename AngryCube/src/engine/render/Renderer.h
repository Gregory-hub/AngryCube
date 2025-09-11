#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "engine/Scene.h"
#include "Shader.h"


class Renderer
{
private:
	GLFWwindow* window;
	glm::mat4 projMatrix;

public:
	Renderer(GLFWwindow* w, glm::vec2 resolution);
	~Renderer();

	Renderer(const Renderer& other) = default;
	Renderer& operator= (const Renderer& other) = default;

	Renderer(Renderer&& other) noexcept;
	Renderer& operator= (Renderer&& other) noexcept;

	void Render(const Scene& scene, Shader& shader) const;
};

