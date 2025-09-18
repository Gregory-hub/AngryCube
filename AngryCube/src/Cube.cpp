#include "Cube.h"

#include <imgui.h>
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/components/mesh/DefaultMeshes.h"


int Cube::id = 0;

Cube::Cube()
	: GameObject(CubeMesh(), Transform())
{
    name = "Cube " + std::to_string(id++);

    physics.Disable();
}

Cube::Cube(const Cube& other)
	: GameObject(other.mesh, other.transform)
{
    name = "Cube " + std::to_string(id++);
}

Cube& Cube::operator=(const Cube& other)
{
    GameObject::operator=(other);
    name = "Cube " + std::to_string(id++);
    return *this;
}

Cube::Cube(Cube&& other) noexcept
	: GameObject(std::move(other.mesh), std::move(other.transform))
{
    name = std::exchange(other.name, "");
}

Cube& Cube::operator=(Cube&& other) noexcept
{
    if (this != &other)
    {
		name = std::exchange(other.name, "");
		GameObject::operator=(std::move(other));
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

float Cube::GetHeight() const
{
    if (const CubeMesh* cubeMesh = dynamic_cast<const CubeMesh*>(&mesh))
		return cubeMesh->GetHeight();
    else
        throw std::runtime_error("mesh is not of type CubeMesh");
}

void Cube::Update(float deltaTime)
{
}

void Cube::ShowDebugControls(glm::vec2 pos)
{
    ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
    ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    GetTransform().ShowDebugControls();

    ImGui::DragFloat2("Push direction", &pushDirection.x, 0.01f, -1.0f, 1.0f);

    if (ImGui::Button("Toggle physics"))
    {
        if (GetPhysics().Enabled())
			GetPhysics().Disable();
        else
			GetPhysics().Enable();
    }
    if (ImGui::Button("Stop"))
    {
		GetPhysics().Stop();
    }
    if (ImGui::Button("Push"))
    {
		GetPhysics().ApplyForce(pushDirection * 10000.0f);
    }

    ImGui::End();
}

