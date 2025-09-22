#include "Cube.h"

#include <stdexcept>

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/components/mesh/DefaultMeshes.h"


int Cube::id = 0;

Cube::Cube()
	:   GameObject(1.0f)
{
    name = "Cube " + std::to_string(id++);
    meshes.push_back(std::make_shared<CubeMesh>());
}

Cube::Cube(float mass)
	:   GameObject(mass)
{
    name = "Cube " + std::to_string(id++);
    meshes.push_back(std::make_shared<CubeMesh>());
}

Cube::Cube(const Cube& other)
	: GameObject(other)
{
    name = "Cube " + std::to_string(id++);
    mass = other.mass;
}

Cube& Cube::operator=(const Cube& other)
{
    if (this != &other)
    {
        GameObject::operator=(other);
        name = "Cube " + std::to_string(id++);
        mass = other.mass;
    }
	return *this;
}

Cube::Cube(Cube&& other) noexcept
	: GameObject(std::move(other)), mass(std::exchange(other.mass, 0.0f))
{
}

Cube& Cube::operator=(Cube&& other) noexcept
{
    if (this != &other)
    {
		mass = std::exchange(other.mass, 0.0f);
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

glm::vec2 Cube::GetLowestPoint() const
{
	return transform.GetTranslation() - glm::vec2(0.0f, GetHeight() / 2);
}

float Cube::GetHeight() const
{
    if (const std::shared_ptr<CubeMesh>& cubeMesh = std::dynamic_pointer_cast<CubeMesh>(meshes[0]))
        return cubeMesh->GetHeight() * transform.GetScale().y;
    else
        throw std::runtime_error("mesh is not of type CubeMesh");
}

float Cube::GetWidth() const
{
    if (const std::shared_ptr<CubeMesh>& cubeMesh = std::dynamic_pointer_cast<CubeMesh>(meshes[0]))
        return cubeMesh->GetWidth() * transform.GetScale().x;
    else
        throw std::runtime_error("mesh is not of type CubeMesh");
}

void Cube::Update(float deltaTime)
{
}

void Cube::OnCollisionStart(const std::shared_ptr<GameObject>& other)
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
		GetPhysics().ApplyForce(pushDirection * 30000.0f);
    }

    ImGui::End();
}

