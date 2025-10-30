#include "pch.h"
#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui.h"
#include "Settings.h"
#include "engine/core/Game.h"


Renderer::Renderer(GLFWwindow* window, glm::vec2 windowResolution)
	: window(window),
	projMatrix(glm::perspective(glm::radians(90.0f), windowResolution.x / windowResolution.y, 0.1f, 10000.0f)),
	viewMatrix(glm::mat4(1.0f))
{
	float worldRatio = worldBounds.x / worldBounds.y;
	float windowRatio = windowResolution.x / windowResolution.y;
	float cameraMoveRatio = worldRatio / windowRatio;
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -500.0f, -500.0f) * cameraMoveRatio);
}

void Renderer::Render(const Scene& scene) const
{
	for (const std::shared_ptr<GameObject>& object : scene.GetObjects())
		RenderObject(object);

	if (Settings::DebugUIEnabled)
		debugUIRenderer.RenderDebugUI(scene);
}

void Renderer::RenderObject(const std::shared_ptr<GameObject>& object) const
{
	for (const std::shared_ptr<Mesh>& mesh : object->GetMeshes())
	{
		if (Shader* shader = mesh->GetShader().get())
		{
			shader->Bind();
			shader->SetUniform("transform", projMatrix * viewMatrix * object->GetTransform().GetMatrix());
			if (const Material* material = mesh->GetMaterial().get())
				material->SetShaderUniforms(shader);
	
			mesh->BindBuffers();
			glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
}
