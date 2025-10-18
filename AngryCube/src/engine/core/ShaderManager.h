#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "engine/render/Shader.h"


class ShaderManager
{
private:
    inline static std::unordered_map<std::type_index, std::shared_ptr<Shader>> shaders;

public:
    template<typename T>
    static std::shared_ptr<Shader> GetShaderFor()
    {
        auto it = shaders.find(std::type_index(typeid(T)));
        if (it != shaders.end()) {
            return it->second;
        }
        return nullptr;
    }

    template<typename T>
    static void RegisterShaderFor(std::shared_ptr<Shader> shader)
    {
        shaders[std::type_index(typeid(T))] = std::move(shader);
    }

    template<typename T>
    static void RemoveShaderFor()
    {
        shaders.erase(std::type_index(typeid(T)));
    }
};
