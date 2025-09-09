#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/Transform.h"


class Mesh
{
protected:
    std::string name;

    std::vector<glm::vec2> vertices;
    std::vector<glm::uvec3> triangles;

    Transform prevTransform;

public:
    Mesh();

    Transform transform;

    virtual std::string GetName() const;

    virtual bool TransformHasChanged() const;

    virtual unsigned int GetVertexCount() const;
    virtual unsigned int GetIndexCount() const;

    virtual void Move(const glm::vec3& value);
    virtual void Rotate(const float value);
    virtual void Scale(const glm::vec3& value);

    virtual void Update(float deltaTime) {};
    virtual void PostUpdate();

    virtual std::vector<glm::vec4> GetVertices() const;
    virtual std::vector<glm::uvec3> GetTriangles() const;

    virtual glm::mat4 GetTransformMatrix() const;

    virtual void ShowDebugControls(glm::vec2 pos) {};
};

