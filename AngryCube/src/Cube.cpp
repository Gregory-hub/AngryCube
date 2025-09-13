#include "Cube.h"

#include <GL/glew.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "engine/mesh/DefaultMeshes.h"


int Cube::id = 0;

Cube::Cube()
{
    mesh = std::make_shared<CubeMesh>();
    movement = std::make_shared<Movement>();
    name = "Cube " + std::to_string(id++);
}

Cube::Cube(const Cube& other)
{
    name = "Cube " + std::to_string(id++);
}

Cube& Cube::operator=(const Cube& other)
{
    name = "Cube " + std::to_string(id++);
    return *this;
}

Cube::Cube(Cube&& other) noexcept
{
    name = std::exchange(other.name, "");
}

Cube& Cube::operator=(Cube&& other) noexcept
{
    if (this != &other)
    {
		name = std::exchange(other.name, "");
    }
    return *this;
}

std::shared_ptr<GameObject> Cube::Clone() const
{
    return std::make_shared<Cube>(*this);
}

std::shared_ptr<GameObject> Cube::MoveClone()
{
    return std::make_shared<Cube>(std::move(*this));
}

void Cube::Update(float deltaTime)
{
}

void Cube::ShowDebugControls(glm::vec2 pos)
{
    ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
    ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    GetMovement()->GetTransform().ShowDebugControls();
    ImGui::End();
}

