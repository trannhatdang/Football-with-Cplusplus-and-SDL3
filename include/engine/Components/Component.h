#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "engine/dg_engine_std.h"
#include <unordered_map>
class GameObject;

class Component
{
	protected:
		std::string m_name = "Component";
		GameObject* gameObject;
	public:
		Component(const std::string& name, GameObject* gameObject);
		~Component();
		virtual void OnStart();
		virtual void OnFixedIterate();
		virtual void OnIterate() = 0;
		virtual void OnDraw(SDL_Renderer* renderer, Vector3 CameraPos);
		virtual void OnEvent(SDL_Event* event);
		virtual std::unique_ptr<Component> copy() = 0;
		std::string GetName() const;
};

#endif
