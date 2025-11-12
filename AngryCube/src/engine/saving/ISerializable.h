#pragma once
#include <json.hpp>


// Use this interface for all savable objects. What and how gets saved is up to game developer
class ISerializable
{
public:
   virtual ~ISerializable() = default;

   virtual nlohmann::json Serialize() = 0;
   virtual void Deserialize(const nlohmann::json& json) = 0;
};
