#include "Scene.h"

#include <GL/glew.h>


Scene::Scene(const Scene& other)
{
    for (std::shared_ptr<GameObject> object : other.objects)
        objects.insert(object->Clone());
}

Scene& Scene::operator=(const Scene& other)
{
    if (this != &other)
    {
        for (std::shared_ptr<GameObject> object : other.objects)
			objects.insert(object->Clone());
    }
    return *this;
}

Scene::Scene(Scene&& other) noexcept
{
	for (std::shared_ptr<GameObject> object : other.objects)
		objects.insert(object->MoveClone());
}

Scene& Scene::operator=(Scene&& other) noexcept
{
    if (this != &other)
    {
		for (std::shared_ptr<GameObject> object : other.objects)
			objects.insert(object->MoveClone());
    }
    return *this;
}

const std::unordered_set<std::shared_ptr<GameObject>>& Scene::GetObjects() const
{
    return objects;
}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
    objects.insert(object);
}

void Scene::Remove(const std::shared_ptr<GameObject>& object)
{
    objects.erase(object);
}

bool Scene::Contains(const std::shared_ptr<GameObject>& object) const
{
    return objects.contains(object);
}

void Scene::Update(float deltaTime) const
{
    for (std::shared_ptr<GameObject> object : objects)
    {
        object->Update(deltaTime);
    }
}

