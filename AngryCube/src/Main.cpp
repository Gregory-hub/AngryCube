#include "pch.h"
#include <iostream>
#include <string>
#include <memory>

#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "engine/core/Game.h"
#include "engine/core/LevelManager.h"
#include "engine/core/ShaderManager.h"
#include "engine/utility/Logger.h"
#include "engine/utility/debugCallback.h"
#include "engine/utility/Clock.h"
#include "engine/utility/Timer.h"
#include "engine/render/Renderer.h"
#include "engine/render/Shader.h"
#include "engine/components/mesh/DefaultMeshes.h"

#include "game/levels/Level1.h"


// TODO:
// (done) logger
// (done) error handling
// (done) render multiple objects (scene)
// (done) optimize multiple object rendering (glBufferSubData)
// (done) file structure (src folder)
// (done) copy and move constructors and operators to all
// (done) optimize multiple object rendering back (no frequent cpu-gpu data transfer)
// (done) game-like architecture
// (skipped) component system with component checking
// (done) physics
// (done) collision
// fix ground physics
// game logic
// saves
// levels
// textures

// TO BE SOLVED:
// components with references to parent must not copy reference in copy and move operations


static glm::ivec2 WINDOW_RESOLUTION = { 1280, 720 };
// static glm::ivec2 WINDOW_RESOLUTION = { 1920, 1080 };

static GLFWwindow* runSetup()
{
    if (!glfwInit())
    {
        std::string message = "GLFW setup failed";
        Logger::Log(LogLevel::Error, message);
        throw std::runtime_error(message);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // disable when releasing
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    //GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    //const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    //glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    //glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    //glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    //glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    //window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);

    GLFWwindow* window = glfwCreateWindow(WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y, "Angry Cube", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        std::string message = "Window setup failed";
        Logger::Log(LogLevel::Error, message);
        throw std::runtime_error(message);
    }

    glfwMakeContextCurrent(window);

    // vsync
    //glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        std::string message = "GLEW setup failed";
        Logger::Log(LogLevel::Error, message);
        throw std::runtime_error(message);
    }

    Logger::Log(LogLevel::Info, reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    return window;
}


void ShowDebugTimeValues(float deltaTime, float framerate)
{
    static float time = 0.0f;
    time += deltaTime;

    ImGui::SetNextWindowPos(ImVec2(WINDOW_RESOLUTION.x - 220.0f, 20.0f));
    ImGui::Begin("Time", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text(("time from start: " + std::to_string(time)).c_str());
	ImGui::Text(("deltaTime: " + std::to_string(deltaTime)).c_str());
	ImGui::Text(("fps: " + std::to_string(static_cast<int>(framerate))).c_str());
	ImGui::End();
}


int main()
{
    GLFWwindow* window = runSetup();

    Clock clock;
    Timer timer;

    Renderer renderer(window, WINDOW_RESOLUTION);

    auto cubeShader = std::make_shared<Shader>("cube");
	ShaderManager::RegisterShaderFor<CubeMesh>(std::move(cubeShader));

    Game game;
    std::shared_ptr<Level> level = std::make_shared<Level1>();
    game.LoadLevel(level);

	glm::vec3 skyColor = glm::vec3(0.568f, 0.78f, 0.98f) * 0.9f;
    glClearColor(skyColor.r, skyColor.g, skyColor.b, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


        timer.Start();
        float deltaTime = clock.Tick();

        game.GetActiveLevel()->Update(deltaTime);
        renderer.Render(game.GetActiveLevel()->GetScene());

        float frametime = timer.End();
        ShowDebugTimeValues(deltaTime, 1.0f / frametime);


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();

        // Demonstrates physics instability when fps is not stable
        //std::this_thread::sleep_for(std::chrono::milliseconds((int)(std::rand() / (float)RAND_MAX * 40)));
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
