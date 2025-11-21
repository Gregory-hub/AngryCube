#pragma once
#include <json.hpp>


// Use this interface for all savable objects
// Uses json as default
class ISerializable
{
public:
   virtual ~ISerializable() = default;

   virtual nlohmann::json Serialize() = 0;
   virtual void Deserialize(const nlohmann::json& json) = 0;
};
