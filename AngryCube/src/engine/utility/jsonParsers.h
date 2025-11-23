#pragma once
#include "pch.h"

#include <json.hpp>


template<typename T>
std::optional<T> parseFromJson(const nlohmann::json& json, const std::string& key)
{
    if (!json.is_null() && json.contains(key) && !json[key].is_null())
        return json[key].get<T>();
    else
        return std::nullopt;
}

template<>
inline std::optional<glm::vec2> parseFromJson(const nlohmann::json& json, const std::string& key)
{
    if (!json.is_null() && json.contains(key) && !json[key].is_null())
    {
        nlohmann::json jsonVec2 = json[key];
        if (!jsonVec2[0].is_null() && !jsonVec2[1].is_null())
            return glm::vec2 { jsonVec2[0].get<float>(), jsonVec2[1].get<float>() };
    }
    else
        return std::nullopt;
}
