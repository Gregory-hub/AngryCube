#include "Movement.h"



Transform& Movement::GetTransform()
{
    return transform;
}

const Transform& Movement::GetTransform() const
{
    return transform;
}

void Movement::Move(const glm::vec2& value)
{
    transform.SetTranslation(transform.GetTranslation() + value);
}

void Movement::Rotate(const float value)
{
    transform.SetRotation(transform.GetRotation() + value);
}

void Movement::Scale(const glm::vec2& value)
{
    transform.SetScale(transform.GetScale() + value);
}

glm::mat4 Movement::GetTransformMatrix() const
{
    return transform.GetMatrix();
}

