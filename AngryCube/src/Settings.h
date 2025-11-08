#pragma once
#include <glm/glm.hpp>


// Should be bound to json settings file
// Now just static class
class Settings
{
public:
     inline static bool Fullscreen = false;
     inline static bool DebugUIEnabled = true;
     inline static glm::ivec2 WindowResolution = { 1280, 720 };
     //inline static glm::ivec2 WindowResolution = { 1920, 1080 };
     //inline static glm::ivec2 WindowResolution = { 720, 720 };
     //inline static glm::ivec2 WindowResolution = { 1280, 480 };
     //inline static glm::ivec2 WindowResolution = { 480, 1280 };

     Settings() = delete;
     Settings(const Settings&) = delete;
     Settings(Settings&&) = delete;
     Settings& operator& (const Settings&) = delete;
     Settings& operator& (Settings&&) = delete;
};
