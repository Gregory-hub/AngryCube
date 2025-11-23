#include "pch.h"
#include "Scene.h"


Scene::Scene()
	: ground(std::make_shared<FlatGround>(this, 0.0f))
{
    Add(ground);
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

    for (const auto& child : object->GetChildren())
    {
		if (!Contains(child))
			Add(child);
    }
}

void Scene::Remove(const std::shared_ptr<GameObject>& object)
{
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
    ground->GetTransform().Enable();
    ground->SetHeight(height);
    ground->GetTransform().Disable();
}

void Scene::Update(float deltaTime)
{
    DestroyObjectsInQueue();

    for (const std::shared_ptr<GameObject>& object : GetObjects())
    {
        object->Update(deltaTime);
        object->GetPhysics().Update(deltaTime);

		for (const std::shared_ptr<GameObject>& other : objects)
		{
            if (object->GetCollision().IsColliding(other))
                object->OnCollisionStart(other);
		}

        object->GetPhysics().PostUpdate(deltaTime);
    }
}

void Scene::AddToDestructionQueue(std::shared_ptr<IDestructable> destroyed)
{
    destructionQueue.push(destroyed);
}

void Scene::DestroyObjectsInQueue()
{
    while (!destructionQueue.empty())
    {
        std::shared_ptr<IDestructable> destroyed = destructionQueue.front();
		destructionQueue.pop();

        if (auto object = std::dynamic_pointer_cast<GameObject>(destroyed))
        {
            destroyed->OnDestructon();
            Remove(object);
        }
    }
}
