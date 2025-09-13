#pragma once

#include <memory>
#include <unordered_set>

#include <glm/glm.hpp>

#include "GameObject.h"


class Scene
{
private:
	std::unordered_set<std::shared_ptr<GameObject>> objects;

public:
	Scene() = default;
	~Scene() = default;

	Scene(const Scene& other);
	Scene& operator= (const Scene& other);

	Scene(Scene&& other) noexcept;
	Scene& operator= (Scene&& other) noexcept;

	const std::unordered_set<std::shared_ptr<GameObject>>& GetObjects() const;

	void Add(const std::shared_ptr<GameObject>& object);
	void Remove(const std::shared_ptr<GameObject>& object);
	bool Contains(const std::shared_ptr<GameObject>& object) const;

	void Update(float deltaTime) const;
};

