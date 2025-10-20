#include "pch.h"
#include "SolidColor.h"

#include "engine/render/Shader.h"


SolidColor::SolidColor(const glm::vec4& defaultColor)
    : color(defaultColor)
{
}

const glm::vec4& SolidColor::GetColor() const
{
    return color;
}

void SolidColor::SetColor(const glm::vec4& newColor)
{
    color = newColor;
}

void SolidColor::SetShaderUniforms(Shader* shader) const
{
    shader->SetUniform<glm::vec4>("color", color);
}
