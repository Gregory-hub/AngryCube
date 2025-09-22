#include "Scene.h"


Scene::Scene()
	: ground(std::make_shared<FlatGround>(0.0f))
{
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

const std::unordered_set<std::shared_ptr<GameObject>>& Scene::GetObjects() const
{
    return objects;
}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
    objects.insert(object);
    if (ground)
        object->GetPhysics()->SetGround(ground);
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

void Scene::SetGround(float height)
{
    ground = std::make_shared<FlatGround>(height);
}

void Scene::Update(float deltaTime) const
{
    for (const std::shared_ptr<GameObject>& object : objects)
    {
		if (ground && !object->GetPhysics()->GetGround())
			object->GetPhysics()->SetGround(ground);

        object->Update(deltaTime);
        object->GetPhysics()->Update(deltaTime);

		for (const std::shared_ptr<GameObject>& other : objects)
		{
			if (object != other && object->GetCollision()->IsColliding(other))
                object->OnCollisionStart(other);
		}
    }
}

