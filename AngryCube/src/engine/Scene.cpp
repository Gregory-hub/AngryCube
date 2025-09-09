#include "Scene.h"

#include <GL/glew.h>


std::vector<std::shared_ptr<Mesh>> Scene::GetMeshes() const
{
    return meshBuffer.GetMeshes();
}

void Scene::BindBuffer() const
{
    meshBuffer.Bind();
}

void Scene::UnbindBuffer() const
{
    meshBuffer.Unbind();
}

void Scene::AddMesh(std::shared_ptr<Mesh>& mesh)
{
    meshBuffer.AddMesh(mesh);
}

void Scene::RemoveMesh(const std::shared_ptr<Mesh>& mesh)
{
    meshBuffer.RemoveMesh(mesh);
}

bool Scene::Contains(const std::shared_ptr<Mesh>& mesh) const
{
    return meshBuffer.Contains(mesh);
}

void Scene::SendMeshesToGPU()
{
    meshBuffer.SetBufferOnGPU();
}

unsigned int Scene::GetVertexCount() const
{
    return meshBuffer.GetVertexCount();
}

unsigned int Scene::GetIndexCount() const
{
    return meshBuffer.GetIndexCount();
}

void Scene::Update(float deltaTime)
{
    for (std::shared_ptr<Mesh> mesh : meshBuffer.GetMeshes())
    {
        mesh->Update(deltaTime);
        if (mesh->TransformHasChanged())
			meshBuffer.UpdateMeshOnGPU(mesh);
        mesh->PostUpdate();
    }
}

