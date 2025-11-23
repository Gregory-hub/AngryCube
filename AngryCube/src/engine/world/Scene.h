#pragma once

#include <memory>
#include <unordered_set>

#include "FlatGround.h"
#include "GameObject.h"
#include "engine/destruction/IDestructableContainer.h"


class Scene : public IDestructableContainer
{
private:
	std::unordered_set<std::shared_ptr<GameObject>> objects;
	std::shared_ptr<FlatGround> ground;
	
    std::queue<std::shared_ptr<IDestructable>> destructionQueue;

public:
	Scene();
	virtual ~Scene() = default;

	Scene(const Scene& other);
	Scene& operator= (const Scene& other);

	Scene(Scene&& other) noexcept;
	Scene& operator= (Scene&& other) noexcept;

	std::unordered_set<std::shared_ptr<GameObject>> GetObjects() const;

	void Add(const std::shared_ptr<GameObject>& object);
	void Remove(const std::shared_ptr<GameObject>& object);
	bool Contains(const std::shared_ptr<GameObject>& object) const;

	const std::shared_ptr<FlatGround>& GetGround() const;
	void SetGroundHeight(float height);

	void Update(float deltaTime);
	
	void AddToDestructionQueue(std::shared_ptr<IDestructable> destroyed) override;
	
private:
	void DestroyObjectsInQueue() override;
};
