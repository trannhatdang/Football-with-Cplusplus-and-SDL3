#ifndef G_OBJECT_
#define G_OBJECT_

#include "Components/Component.h"
#include "Components/Transform.h"
#include <unordered_map>
class Scene;

class GameObject
{
	private:
		std::unordered_map<std::string, Component*> m_comp_map;
		std::vector<std::unique_ptr<Component>> m_components;
		std::string m_name;
		std::string m_tag;
		Scene* m_scene;
	public:
		GameObject(Scene* scene, std::string name = "GameObject", std::string tag = "Entity");
		GameObject(const GameObject& gameObject);
		void OnStart();
		void OnIterate();
		void OnFixedIterate();
		void OnDraw(SDL_Renderer* renderer);
		void OnEvent(SDL_Event* event);
		void OnCollisionEnter(GameObject* obj);
		void OnTriggerEnter(GameObject* obj);
		Component* GetComponent(int index) const;
		Component* GetComponent(const std::string& name) const;
		Transform* GetTransform() const;
		std::string GetName() const;
		std::string GetTag() const;
		Scene* GetScene() const;
		Component* AddComponent(Component* component);
		Component* CopyComponent(const std::unique_ptr<Component>& component);
};

#endif
