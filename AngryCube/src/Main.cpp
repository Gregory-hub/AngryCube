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

#include "Settings.h"
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
#include "engine/UI/HUD.h"
#include "engine/UI/Widget.h"

#include "game/CatapultController.h"
#include "game/levels/AngryCubeLevel.h"
#include "game/levels/LevelSaveManager.h"
#include "game/UI/GameplayHUD.h"


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
// (done) fix ground physics
// (done) make Collision abstract
// (done) use CubeCollision subclass
// (done kinda) separate world space from screen coordinates
// game logic
// catapult release angle controls
// UI
// saves
// levels
// textures


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

    GLFWwindow* window;
    if (Settings::Fullscreen)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
        glfwGetWindowSize(window, &Settings::NoFullscreenWindowResolution.x, &Settings::NoFullscreenWindowResolution.y);
    }
    else
    {
        window = glfwCreateWindow(Settings::NoFullscreenWindowResolution.x, Settings::NoFullscreenWindowResolution.y, "Angry Cube", NULL, NULL);
    }
    Settings::SetWindow(window);

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
    if (!Settings::DebugUIEnabled)
        return;

    static float time = 0.0f;
    time += deltaTime;

    ImGui::SetNextWindowPos(ImVec2(Settings::NoFullscreenWindowResolution.x - 220.0f, 20.0f));
    ImGui::Begin("Time", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text(("time from start: " + std::to_string(time)).c_str());
	ImGui::Text(("deltaTime: " + std::to_string(deltaTime)).c_str());
	ImGui::Text(("fps: " + std::to_string(static_cast<int>(framerate))).c_str());
	ImGui::End();
}

void ShowDebugLevelSaveWindow(std::shared_ptr<AngryCubeLevel> level)
{
    if (!Settings::DebugUIEnabled)
        return;

    static std::string levelName;
    levelName.reserve(64);

    ImGui::SetNextWindowPos(ImVec2(Settings::NoFullscreenWindowResolution.x - 330.0f, 140.0f));
    ImGui::Begin("Level", nullptr);

    bool changed = ImGui::InputText("Level name", levelName.data(), levelName.capacity());
    if (changed)
        levelName.resize(strlen(levelName.data()));

    if (ImGui::Button("Save level"))
    {
        if (!levelName.empty())
        {
            auto levelCopy = std::make_shared<AngryCubeLevel>(*level);
            levelCopy->SetName(levelName);
            LevelSaveManager::SaveLevel(levelCopy);
            levelName.clear();
        }
    }
	ImGui::End();
}


int main()
{
    GLFWwindow* window = runSetup();

    Clock clock;
    Timer timer;

    Renderer renderer(window, Settings::NoFullscreenWindowResolution);

    auto cubeShader = std::make_shared<Shader>("cube");
	ShaderManager::RegisterShaderFor<CubeMesh>(std::move(cubeShader));

    Game game;

    auto level = LevelSaveManager::LoadLevel("levelFiveBricks");

    game.LoadLevel(level);

    auto controller = std::make_shared<CatapultController>(level->GetCatapult());

    GameplayHUD hud(controller);

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
        hud.Render();
  
        float frametime = timer.End();
        ShowDebugTimeValues(deltaTime, 1.0f / frametime);

        ShowDebugLevelSaveWindow(level);


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  
		glfwSwapBuffers(window);
		glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
