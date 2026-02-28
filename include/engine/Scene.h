#ifndef SCENE_H_
#define SCENE_H_

#include "GameObject.h"
#include "Components/BoxCollider.h"

class Scene
{
	private:
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
		std::vector<BoxCollider*> m_colliders;
		std::string m_name;
		void (*m_changeSceneCallback)(int);
		SDL_Renderer* m_renderer;
		SDL_Window* m_window;
	public:
		Scene(const std::string& name = "Scene", void (*changeSceneCallback)(int) = nullptr, SDL_Renderer* renderer = nullptr, SDL_Window* window = nullptr);
		~Scene();
		void OnStart();
		void OnIterate();
		void OnFixedIterate();
		void OnDraw(SDL_Renderer* renderer);
		void OnEvent(SDL_Event* event);
		void RegisterCollider(BoxCollider* coll);
		GameObject* AddGameObject(const std::string& name = "GameObject", const std::string& tag = "Tag");
		GameObject* GetGameObject(int index = 0);
		GameObject* GetGameObject(const std::string& name = "GameObject");
		SDL_Renderer* GetRenderer() const;
		SDL_Window* GetWindow() const;
		const std::vector<BoxCollider*>& GetColliders() const;


		void DEBUG_PrintGameObjAdd() const;
};

#endif
