#include "Scene.h"


const std::unordered_set<std::shared_ptr<Model>>& Scene::GetModels() const
{
    return models;
}

void Scene::AddModel(std::shared_ptr<Model> model)
{
    if (!models.contains(model))
    {
        models.insert(model);
    }
}

void Scene::RemoveModel(std::shared_ptr<Model> model)
{
    if (models.contains(model))
    {
        models.erase(model);
    }
}

bool Scene::Contains(std::shared_ptr<Model> model) const
{
    return models.contains(model);
}

