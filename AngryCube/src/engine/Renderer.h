#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Scene.h"
#include "Shader.h"


class Renderer
{
private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

	GLFWwindow* window;
	glm::mat4 projMatrix;

	Scene scene;

public:
	Renderer(GLFWwindow* w, glm::vec2 resolution);
	~Renderer();

	void SetScene(const Scene& scene);
	void Render(Shader& shader) const;
};

