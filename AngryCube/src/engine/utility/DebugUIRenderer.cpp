#include "pch.h"
#include "DebugUIRenderer.h"

#include "engine/world/GameObject.h"
#include "engine/world/Scene.h"


void DebugUIRenderer::RenderDebugUI(const Scene& scene) const
{
	std::unordered_set<std::shared_ptr<GameObject>> objectsSet = scene.GetObjects();

	std::vector<std::shared_ptr<GameObject>> objects;
	std::copy_if(objectsSet.begin(), objectsSet.end(), std::back_inserter(objects), [](auto obj){ return !obj->GetParent(); } );
	std::sort(objects.begin(), objects.end(), [](auto a, auto b) { return a->GetName() < b->GetName(); });

	ImGui::Begin("Scene");
	for (const std::shared_ptr<GameObject>& object : objects)
	{
		if (!object->GetParent())
			RenderParentObjectDebugUI(object);
	}
	ImGui::End();
}

void DebugUIRenderer::RenderParentObjectDebugUI(const std::shared_ptr<GameObject>& object) const
{
	ImGui::PushID(object->GetName().c_str());
	if (ImGui::CollapsingHeader(object->GetName().c_str()))
	{
		RenderObjectDebugUI(object);
	}
	ImGui::PopID();
}

void DebugUIRenderer::RenderChildObjectDebugUI(const std::shared_ptr<GameObject>& object) const
{
	ImGui::PushID(object->GetName().c_str());
	if (ImGui::TreeNode(object->GetName().c_str()))
	{
		RenderObjectDebugUI(object);
		ImGui::TreePop();
	}
	ImGui::PopID();
}

void DebugUIRenderer::RenderObjectDebugUI(const std::shared_ptr<GameObject>& object) const
{
	object->ShowDebugControls();
	
	std::unordered_set<std::shared_ptr<GameObject>> objectsSet = object->GetChildren();
	std::vector<std::shared_ptr<GameObject>> objects(objectsSet.begin(), objectsSet.end());
	std::sort(objects.begin(), objects.end(), [](auto a, auto b) { return a->GetName() < b->GetName(); });
	for (const auto& child : objects)
		RenderChildObjectDebugUI(child);
}
