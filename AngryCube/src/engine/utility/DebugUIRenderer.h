#pragma once

class GameObject;
class Scene;

class DebugUIRenderer
{
public:
	void RenderDebugUI(const Scene& scene) const;

private:
	void RenderParentObjectDebugUI(const std::shared_ptr<GameObject>& object) const;
	void RenderChildObjectDebugUI(const std::shared_ptr<GameObject>& object) const;
	void RenderObjectDebugUI(const std::shared_ptr<GameObject>& object) const; 
};
