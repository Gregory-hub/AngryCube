#pragma once

#include <GL/glew.h>
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
	
	void RenderDebugUI(const Scene& scene) const;
	void RenderParentObjectDebugUI(const std::shared_ptr<GameObject>& object) const;
	void RenderChildObjectDebugUI(const std::shared_ptr<GameObject>& object) const;
	void RenderObjectDebugUI(const std::shared_ptr<GameObject>& object) const;
};

