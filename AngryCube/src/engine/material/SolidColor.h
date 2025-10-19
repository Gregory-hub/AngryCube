#pragma once
#include <glm/glm.hpp>

#include "Material.h"


class SolidColor : public Material
{
private:
    glm::vec4 color;

public:
    SolidColor(const glm::vec4& defaultColor);

    const glm::vec4& GetColor() const;
    void SetColor(const glm::vec4& color);

    void SetShaderUniforms(Shader* shader) const override;
};
