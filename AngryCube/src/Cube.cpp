#include "Cube.h"

#include <GL/glew.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


int Cube::id = 0;

Cube::Cube()
{
    name = "Cube " + std::to_string(id++);

    vertices = {
        { -50.0f, -50.0f },
        { 50.0f, -50.0f },
        { 50.0f, 50.0f },
        { -50.0, 50.0f }
    };

    indices = {
        { 0, 1, 3 },
        { 1, 2, 3 }
    };
}

std::vector<glm::vec4> Cube::GetVertices() const
{
    std::vector<glm::vec4> result;
    result.reserve(vertices.size());

	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, translation);
	transform = glm::rotate(transform, glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
	transform = glm::scale(transform, scale);

    for (glm::vec2 vertex : vertices)
        result.push_back(transform * glm::vec4(vertex, 0.0f, 1.0f));
	return result;
}

std::vector<glm::uvec3> Cube::GetTriangles() const
{
	return indices;
}

void Cube::ShowDebugControls(glm::vec2 pos)
{
    ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
    ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::DragFloat3("Translation", &translation.x);
    ImGui::DragFloat("Rotation", &rotation);
    ImGui::DragFloat3("Scale", &scale.x, 0.01f);
    ImGui::End();
}

