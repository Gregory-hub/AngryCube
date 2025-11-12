#pragma once
#include "pch.h"

#include <json.hpp>


inline glm::vec2 jsonVec2ToVec2(const nlohmann::json& jsonVec2)
{
    if (!jsonVec2.is_null() && !jsonVec2[0].is_null() && !jsonVec2[1].is_null())
        return { jsonVec2[0].get<float>(), jsonVec2[1].get<float>() };
    else
        throw std::invalid_argument("Level json file is corrupted");
}
