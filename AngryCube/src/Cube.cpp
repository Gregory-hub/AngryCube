#include "Cube.h"

#include <GL/glew.h>


Cube::Cube()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
}

Cube::~Cube()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void Cube::Bind() const
{
    glBindVertexArray(vao);
}

void Cube::Unbind() const
{
    glBindVertexArray(0);
}

void Cube::Move(const glm::vec3& value)
{
	translation += value;
}

void Cube::Rotate(const float value)
{
    rotation += value;
}

void Cube::Scale(const glm::vec3& value)
{
    scale *= value;
}

unsigned int Cube::GetIndexCount() const
{
    return sizeof(indices) / sizeof(unsigned int);
}

glm::mat4 Cube::GetTransformMatrix() const
{
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, translation);
	transform = glm::rotate(transform, glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
	transform = glm::scale(transform, scale);
    return transform;
}

