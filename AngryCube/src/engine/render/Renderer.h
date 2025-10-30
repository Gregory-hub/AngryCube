#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "engine/world/Scene.h"
#include "Shader.h"
#include "engine/utility/DebugUIRenderer.h"


class Renderer
{
private:
	GLFWwindow* window;

	DebugUIRenderer debugUIRenderer;

	glm::vec2 worldBounds{ 2000.0f, 2000.0f / 1.777778f };

	glm::mat4 projMatrix;
	glm::mat4 viewMatrix;

public:
	Renderer(GLFWwindow* w, glm::vec2 windowResolution);
	~Renderer() = default;

	Renderer(const Renderer& other) = default;
	Renderer& operator= (const Renderer& other) = default;

	Renderer(Renderer&& other) noexcept = default;
	Renderer& operator= (Renderer&& other) noexcept = default;

	void Render(const Scene& scene) const;
	void RenderObject(const std::shared_ptr<GameObject>& object) const;
};

