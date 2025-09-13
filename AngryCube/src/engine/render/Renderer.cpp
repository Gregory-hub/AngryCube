#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


Renderer::Renderer(GLFWwindow* window, glm::vec2 resolution)
	: window(window), projMatrix(glm::ortho(0.0f, resolution.x, 0.0f, resolution.y, -1.0f, 1.0f)) { }

Renderer::Renderer(Renderer&& other) noexcept
{
		window = std::exchange(other.window, nullptr);
	projMatrix = std::exchange(other.projMatrix, glm::mat4());
}

Renderer& Renderer::operator=(Renderer&& other) noexcept
{
	if (this != &other)
	{
		window = std::exchange(other.window, nullptr);
		projMatrix = std::exchange(other.projMatrix, glm::mat4());
	}
	return *this;
}

void Renderer::Render(const Scene& scene, Shader& shader) const
{
	shader.Bind();

	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	glm::vec2 debugControlsPos = { 20, 20 };
	for (const std::shared_ptr<GameObject>& object : scene.GetObjects())
	{
		shader.SetUniform("transform", projMatrix * object->GetMovement()->GetTransform().GetMatrix());
		object->ShowDebugControls(debugControlsPos);
		debugControlsPos += glm::vec2({ 0, 120 });
		object->GetMesh()->BindBuffers();
		glDrawElements(GL_TRIANGLES, object->GetMesh()->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
	glfwPollEvents();
}

