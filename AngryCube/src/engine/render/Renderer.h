#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "engine/world/Scene.h"
#include "Shader.h"


class Renderer
{
private:
	GLFWwindow* window;
	glm::mat4 projMatrix;

public:
	Renderer(GLFWwindow* w, glm::vec2 resolution);
	~Renderer() = default;

	Renderer(const Renderer& other) = default;
	Renderer& operator= (const Renderer& other) = default;

	Renderer(Renderer&& other) noexcept;
	Renderer& operator= (Renderer&& other) noexcept;

	void Render(const Scene& scene, Shader& shader) const;
};

