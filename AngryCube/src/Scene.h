#pragma once

#include <memory>
#include <unordered_set>

#include "Model.h"


class Scene
{
private:
	std::unordered_set<std::shared_ptr<Model>> models;

public:
	const std::unordered_set<std::shared_ptr<Model>>& GetModels() const;

	void AddModel(std::shared_ptr<Model> model);
	void RemoveModel(std::shared_ptr<Model> model);
	bool Contains(std::shared_ptr<Model> model) const;
};

