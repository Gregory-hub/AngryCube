#pragma once
#include <glm/glm.hpp>


// Should be bound to json settings file
// Now just static class
class Settings
{
public:
     inline static bool Fullscreen = false;
     inline static bool DebugUIEnabled = false;
     inline static glm::ivec2 NoFullscreenWindowResolution = { 1280, 720 };
     //inline static glm::ivec2 NoFullscreenWindowResolution = { 1920, 1080 };
     //inline static glm::ivec2 NoFullscreenWindowResolution = { 720, 720 };
     //inline static glm::ivec2 NoFullscreenWindowResolution = { 1280, 480 };
     //inline static glm::ivec2 NoFullscreenWindowResolution = { 480, 1280 };

     inline static float killY = -100.0f;

     inline static GLFWwindow* Window;

     static void SetWindow(GLFWwindow* window)
     {
          Window = window;
     }

     static glm::ivec2 GetWindowResolution()
     {
          int width = 0;
          int height = 0;
          if (Window)
               glfwGetWindowSize(Window, &width, &height);
          return { width, height };
     }

     Settings() = delete;
     Settings(const Settings&) = delete;
     Settings(Settings&&) = delete;
     Settings& operator& (const Settings&) = delete;
     Settings& operator& (Settings&&) = delete;
};
