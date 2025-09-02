#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Cube.h"
#include "Shader.h"


// TODO:
// logger
// error handling
// render multiple objects (scene)
// textures

glm::vec2 WINDOW_RESOLUTION = { 1280, 720 };


GLFWwindow* runSetup()
{
    if (!glfwInit())
        throw std::runtime_error("GLFW setup failed");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

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
        throw std::runtime_error("Window setup failed");
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw std::runtime_error("GLEW setup failed");
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

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

    glm::mat4 projMatrix = glm::ortho(0.0f, WINDOW_RESOLUTION.x, 0.0f, WINDOW_RESOLUTION.y, 0.1f, 100.0f);
    //glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), WINDOW_RESOLUTION.x / WINDOW_RESOLUTION.y, 0.1f, 10000.0f);

    Cube cube;
    Shader shader("cube");

	cube.Bind();
	shader.Bind();

	cube.Move({ 640.0f, 360.0f, 0.0f });

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


		float timeValue = glfwGetTime();
		float red = (sin(timeValue) / 2.0f) + 0.5f;
		float green = (cos(1.6 * timeValue) / 2.0f) + 0.5f;
		float blue = (sin(0.3 * timeValue) / 2.0f) + 0.5f;

		cube.Move(glm::vec3({ 0.0f, 0.02f, 0.0f }) * sin(timeValue));
		cube.Rotate(0.005f);
        cube.Scale(glm::vec3(0.00015f, -0.0002f, 0.0f) * sin(timeValue) + 1.0f);

        shader.SetUniform<glm::vec4>("vertexColor", { red, green, blue, 1.0f });
        shader.SetUniform<glm::mat4>("MVP", projMatrix * cube.GetTransformMatrix());

        cube.ShowDebugControls();


        glDrawElements(GL_TRIANGLES, cube.GetIndexCount(), GL_UNSIGNED_INT, nullptr);

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

