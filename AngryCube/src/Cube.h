#pragma once

#include "Vector.h"


class Cube
{
private:
    Vector2<float> vertices[4] = {
        { -0.5f, -0.5f },
        { 0.5f, -0.5f },
        { 0.5f, 0.5f },
        { -0.5f, 0.5f }
    };

    Vector3<unsigned int> indices[2] = {
        { 0, 1, 3 },
        { 1, 2, 3 }
    };

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

public:
    Cube();
    ~Cube();

    void Bind();
    void Unbind();
};

