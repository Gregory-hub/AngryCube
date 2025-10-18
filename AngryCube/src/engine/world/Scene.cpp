#include "Scene.h"


Scene::Scene()
	: ground(std::make_shared<FlatGround>(this, 0.0f))
{
    // Add(ground);
}

Scene::Scene(const Scene& other)
{
    for (const std::shared_ptr<GameObject>& object : other.objects)
        objects.insert(object->Clone());
}

Scene& Scene::operator=(const Scene& other)
{
    if (this != &other)
    {
        for (const std::shared_ptr<GameObject>& object : other.objects)
			objects.insert(object->Clone());
    }
    return *this;
}

Scene::Scene(Scene&& other) noexcept
{
	for (const std::shared_ptr<GameObject>& object : other.objects)
		objects.insert(object->MoveClone());
}

Scene& Scene::operator=(Scene&& other) noexcept
{
    if (this != &other)
    {
		for (const std::shared_ptr<GameObject>& object : other.objects)
			objects.insert(object->MoveClone());
    }
    return *this;
}

std::unordered_set<std::shared_ptr<GameObject>> Scene::GetObjects() const
{
    return objects;
}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
    if (objects.contains(object))
        return;

    objects.insert(object);
    if (ground)
        object->GetPhysics().SetGround(ground);

    for (const auto& child : object->GetChildren())
    {
        Add(child);
    }
}

void Scene::Remove(const std::shared_ptr<GameObject>& object)
{
    if (object->GetPhysics().GetGround())
        object->GetPhysics().SetGround(nullptr);
    objects.erase(object);
}

bool Scene::Contains(const std::shared_ptr<GameObject>& object) const
{
    return objects.contains(object);
}

const std::shared_ptr<FlatGround>& Scene::GetGround() const
{
    return ground;
}

void Scene::SetGroundHeight(float height)
{
    ground->SetHeight(height);
}

void Scene::Update(float deltaTime) const
{
    for (const std::shared_ptr<GameObject>& object : GetObjects())
    {
		if (ground && !object->GetPhysics().GetGround())
			object->GetPhysics().SetGround(ground);

        object->Update(deltaTime);
        object->GetPhysics().Update(deltaTime);

		for (const std::shared_ptr<GameObject>& other : objects)
		{
			if (object != other && object->GetCollision().IsColliding(other))
                object->OnCollisionStart(other);
		}
    }
}
