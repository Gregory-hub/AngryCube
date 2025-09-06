#pragma once

#include <memory>
#include <vector>
#include <unordered_set>

#include <glm/glm.hpp>

#include "Model.h"


class Scene
{
private:
	std::unordered_set<std::shared_ptr<Model>> models;
	unsigned int vertexCount = 0;
	unsigned int indexCount = 0;

public:
	const std::unordered_set<std::shared_ptr<Model>>& GetModels() const;

	void AddModel(std::shared_ptr<Model> model);
	void RemoveModel(std::shared_ptr<Model> model);
	bool Contains(std::shared_ptr<Model> model) const;

	unsigned int GetVertexCount() const;
	unsigned int GetIndexCount() const;
};

