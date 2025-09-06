#include "Scene.h"

#include <GL/glew.h>


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

