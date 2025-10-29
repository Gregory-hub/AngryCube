#include "pch.h"
#include "Renderer.h"

#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui.h"
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

	RenderDebugUI(scene);
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

void Renderer::RenderDebugUI(const Scene& scene) const
{
	std::unordered_set<std::shared_ptr<GameObject>> objectsSet = scene.GetObjects();

	std::vector<std::shared_ptr<GameObject>> objects;
	std::copy_if (objectsSet.begin(), objectsSet.end(), std::back_inserter(objects), [](auto obj){ return !obj->GetParent(); } );
	std::sort(objects.begin(), objects.end(), [](auto a, auto b) { return a->GetName() < b->GetName(); });

	ImGui::Begin("Scene");
	for (const std::shared_ptr<GameObject>& object : objects)
	{
		if (!object->GetParent())
			RenderParentObjectDebugUI(object);
	}
	ImGui::End();
}

void Renderer::RenderParentObjectDebugUI(const std::shared_ptr<GameObject>& object) const
{
	ImGui::PushID(object->GetName().c_str());
	if (ImGui::CollapsingHeader(object->GetName().c_str()))
	{
		RenderObjectDebugUI(object);
	}
	ImGui::PopID();
}

void Renderer::RenderChildObjectDebugUI(const std::shared_ptr<GameObject>& object) const
{
	ImGui::PushID(object->GetName().c_str());
	if (ImGui::TreeNode(object->GetName().c_str()))
	{
		RenderObjectDebugUI(object);
		ImGui::TreePop();
	}
	ImGui::PopID();
}

void Renderer::RenderObjectDebugUI(const std::shared_ptr<GameObject>& object) const
{
	object->ShowDebugControls();
	
	std::unordered_set<std::shared_ptr<GameObject>> objectsSet = object->GetChildren();
	std::vector<std::shared_ptr<GameObject>> objects(objectsSet.begin(), objectsSet.end());
	std::sort(objects.begin(), objects.end(), [](auto a, auto b) { return a->GetName() < b->GetName(); });
	for (const auto& child : objects)
		RenderChildObjectDebugUI(child);
}
