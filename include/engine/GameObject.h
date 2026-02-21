#ifndef G_OBJECT_
#define G_OBJECT_

#include "Components/Component.h"
#include <unordered_map>
#include "Components/Transform.h"

class GameObject
{
	private:
		std::vector<std::unique_ptr<Component>> m_components;
		std::string m_name;
		std::string m_tag;
		std::unordered_map<std::string, Component*> m_comp_map;
	public:
		GameObject(std::string name = "GameObject", std::string tag = "Entity");
		GameObject(const GameObject& gameObject);
		void OnStart();
		void OnIterate();
		void OnFixedIterate();
		void OnDraw(SDL_Renderer* renderer, Vector3 CameraPos);
		void OnEvent(SDL_Event* event);
		void OnCollisionEnter(GameObject* obj);
		const Component* GetComponent(int index) const;
		const Component* GetComponent(const std::string& name) const;
		bool AddComponent(Component* component);
		bool CopyComponent(const std::unique_ptr<Component>& component);
		Component* GetTransform();
};

#endif
