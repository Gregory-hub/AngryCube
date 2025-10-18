#pragma once
#include <memory>

class Shader;


class Material
{
public:
    Material() = default;
    virtual ~Material() = 0;

    Material(const Material& other) = default;
    Material(Material&& other) noexcept = default;

    Material& operator=(const Material& other) = default;
    Material& operator=(Material&& other) noexcept = default;

    virtual void SetShaderUniforms(Shader* shader) const {}
};

inline Material::~Material() = default;
