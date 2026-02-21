#ifndef SCENE_H_
#define SCENE_H_

#include "GameObject.h"

class Scene
{
	private:
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
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
		void OnDraw(SDL_Renderer* renderer, Vector3 CameraPos);
		void OnEvent(SDL_Event* event);
		void AddGameObject();
		GameObject* GetGameObject(int index = 0);
		SDL_Renderer* GetRenderer() const;
		SDL_Window* GetWindow() const;
};

#endif
