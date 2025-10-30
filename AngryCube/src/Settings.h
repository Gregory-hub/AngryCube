#pragma once
#include <glm/glm.hpp>


// Should be bound to json settings file
// Now is recompiled on every change
class Settings
{
public:
     inline static bool Fullscreen = true;
     inline static bool DebugUIEnabled = false;
     inline static glm::ivec2 WindowResolution = { 1280, 720 };
     //inline static glm::ivec2 WindowResolution = { 1920, 1080 };
     //inline static glm::ivec2 WindowResolution = { 720, 720 };
     //inline static glm::ivec2 WindowResolution = { 1280, 480 };
     //inline static glm::ivec2 WindowResolution = { 480, 1280 };
};
