#include "Renderer.h"

#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui.h"
#include "engine/core/Game.h"


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

	for (const std::shared_ptr<GameObject>& object : scene.GetObjects())
		RenderObject(object, shader);

	RenderDebugUI(scene);
}

void Renderer::RenderObject(const std::shared_ptr<GameObject>& object, Shader& shader) const
{
	shader.SetUniform("transform", projMatrix * object->GetTransform().GetMatrix());

	for (const std::shared_ptr<Mesh>& mesh : object->GetMeshes())
	{
		mesh->BindBuffers();
		glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
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
