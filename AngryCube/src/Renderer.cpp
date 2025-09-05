#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


Renderer::Renderer(GLFWwindow* window, glm::vec2 resolution)
	: window(window), projMatrix(glm::ortho(0.0f, resolution.x, 0.0f, resolution.y, 0.1f, 100.0f)) {}

void Renderer::Render(const Scene& scene, Shader& shader) const
{
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	glm::vec2 debugControlsPos = { 20, 20 };
	for (std::shared_ptr<Model> model : scene.GetModels())
	{
		model->ShowDebugControls(debugControlsPos);
		debugControlsPos += glm::vec2({ 0, 120 });
		model->Bind();
		shader.SetUniform<glm::mat4>("MVP", projMatrix * model->GetTransformMatrix());
		glDrawElements(GL_TRIANGLES, model->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
	glfwPollEvents();
}
