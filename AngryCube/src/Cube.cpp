#include "Cube.h"

#include <GL/glew.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


int Cube::id = 0;

Cube::Cube()
    : startingTranslation(glm::vec3()), startingScale(glm::vec3())
{
    name = "Cube " + std::to_string(id++);

    vertices = {
        { -50.0f, -50.0f },
        { 50.0f, -50.0f },
        { 50.0f, 50.0f },
        { -50.0, 50.0f }
    };

    triangles = {
        { 0, 1, 3 },
        { 1, 2, 3 }
    };
}

void Cube::Update(float deltaTime)
{
 //   if (!startedMovement)
 //   {
 //       startingTranslation = transform.GetTranslation();
 //       startingScale = transform.GetScale();
 //       startedMovement = true;
 //   }
	//transform.SetTranslation(startingTranslation + glm::vec3({ 0.0f, 75.0f, 0.0f }) * sin(2.0f * x));
	//Rotate(50.0f * speed * deltaTime);
	//transform.SetScale(startingScale + startingScale * glm::vec3(0.8f, -0.5f, 0.0f) * sin(1.0f * x));

 //   x += speed * deltaTime;
}

void Cube::ShowDebugControls(glm::vec2 pos)
{
    ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
    ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    transform.ShowDebugControls();
    ImGui::DragFloat("Speed", &speed, 0.01f);
    ImGui::End();
}

