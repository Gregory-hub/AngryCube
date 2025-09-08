#include "Scene.h"

#include <GL/glew.h>


Scene::Scene(const Scene& other)
{
    vertexCount = other.vertexCount;
    indexCount = other.indexCount;
    for (std::shared_ptr<Model> model : other.models)
        models.insert(model);
}

Scene& Scene::operator=(const Scene& other)
{
    vertexCount = other.vertexCount;
    indexCount = other.indexCount;
    for (std::shared_ptr<Model> model : other.models)
        models.insert(model);
    return *this;
}

const std::unordered_set<std::shared_ptr<Model>>& Scene::GetModels() const
{
    return models;
}

void Scene::AddModel(std::shared_ptr<Model> model)
{
    if (!models.contains(model))
    {
        models.insert(model);
        vertexCount += model->GetVertexCount();
        indexCount += model->GetIndexCount();
    }
}

void Scene::RemoveModel(std::shared_ptr<Model> model)
{
    if (models.contains(model))
    {
        models.erase(model);
        vertexCount -= model->GetVertexCount();
        indexCount -= model->GetIndexCount();
    }
}

bool Scene::Contains(std::shared_ptr<Model> model) const
{
    return models.contains(model);
}

unsigned int Scene::GetVertexCount() const
{
    return vertexCount;
}

unsigned int Scene::GetIndexCount() const
{
    return indexCount;
}

void Scene::Update(float deltaTime)
{
    for (std::shared_ptr<Model> model : models)
        model->Update(deltaTime);
}

