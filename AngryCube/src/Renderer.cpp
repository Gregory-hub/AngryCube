#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


Renderer::Renderer(GLFWwindow* window, glm::vec2 resolution)
	: window(window), projMatrix(glm::ortho(0.0f, resolution.x, 0.0f, resolution.y, 0.1f, 100.0f))
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
}

Renderer::~Renderer()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void Renderer::Render(const Scene& scene, Shader& shader) const
{
	std::vector<glm::vec4> vertices;
	vertices.reserve(scene.GetVertexCount());
	std::vector<unsigned int> indices;
	indices.reserve(scene.GetIndexCount());

	unsigned int triangleOffset = 0;
	for (std::shared_ptr<Model> model : scene.GetModels())
	{
		for (glm::vec4 vertex : model->GetVertices())
			vertices.push_back(projMatrix * vertex);
		for (glm::uvec3 triangle : model->GetTriangles())
		{
			indices.push_back(triangle.x + triangleOffset);
			indices.push_back(triangle.y + triangleOffset);
			indices.push_back(triangle.z + triangleOffset);
		}
		triangleOffset += model->GetVertexCount();
	}

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	glm::vec2 debugControlsPos = { 20, 20 };
	for (std::shared_ptr<Model> model : scene.GetModels())
	{
		model->ShowDebugControls(debugControlsPos);
		debugControlsPos += glm::vec2({ 0, 120 });
	}
	glDrawElements(GL_TRIANGLES, scene.GetIndexCount(), GL_UNSIGNED_INT, nullptr);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
	glfwPollEvents();
}

