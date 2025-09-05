#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Logger.h"
#include "debugCallback.h"
#include "Scene.h"
#include "Cube.h"
#include "Shader.h"
#include "Renderer.h"


// TODO:
// (done) logger
// (done) error handling
// render multiple objects (scene)
// physics
// game logic
// textures

glm::vec2 WINDOW_RESOLUTION = { 1280, 720 };


GLFWwindow* runSetup()
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

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        std::string message = "GLEW setup failed";
        Logger::Log(LogLevel::Error, message);
        throw std::runtime_error(message);
    }

    Logger::Log(Info, reinterpret_cast<const char*>(glGetString(GL_VERSION)));

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


int main()
{
    GLFWwindow* window = runSetup();

    Shader shader("cube");
	shader.Bind();

    Scene scene;

    std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    cube->SetTranslation({ 990.0f, 360.0f, -1.0f });
    cube->SetScale(glm::vec3(1.5f, 1.5f, 0.0f));
    scene.AddModel(cube);

    std::shared_ptr<Cube> cube1 = std::make_shared<Cube>();
    cube1->SetTranslation({ 440.0f, 460.0f, -1.0f });
    scene.AddModel(cube1);

    std::shared_ptr<Cube> cube2 = std::make_shared<Cube>();
    cube2->SetTranslation({ 640.0f, 260.0f, -1.0f });
    cube2->SetScale(glm::vec3(0.5f, 1.5f, 0.0f));
    scene.AddModel(cube2);

    Renderer renderer(window, WINDOW_RESOLUTION);

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
		float timeValue = glfwGetTime();
		float red = (sin(timeValue) / 2.0f) + 0.5f;
		float green = (cos(1.6 * timeValue) / 2.0f) + 0.5f;
		float blue = (sin(0.3 * timeValue) / 2.0f) + 0.5f;

		cube->Move(glm::vec3({ 0.0f, 0.02f, 0.0f }) * sin(timeValue));
		cube->Rotate(0.005f);
        cube->Scale(glm::vec3(0.0004f, -0.0001f, 0.0f) * sin(2.0f * timeValue));

		cube1->Move(glm::vec3({ 0.01f, 0.0f, 0.0f }) * sin(timeValue));
		cube1->Rotate(-0.008f);
        cube1->Scale(glm::vec3(0.0004f, -0.0001f, 0.0f) * sin(3.0f * timeValue));

		cube2->Move(glm::vec3({ -0.001f, 0.01f, 0.0f }) * cos(timeValue));
		cube2->Rotate(0.002f);
        cube2->Scale(glm::vec3(0.0003f, -0.00015f, 0.0f) * sin(1.0f * timeValue));

		shader.SetUniform<glm::vec4>("vertexColor", { red, green, blue, 1.0f });
        renderer.Render(scene, shader);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

