#include "engine/Scene.h"

Scene::Scene(const std::string& name, void (*changeSceneCallback)(int), SDL_Renderer* renderer, SDL_Window* window) : m_name(name), m_changeSceneCallback(changeSceneCallback), m_renderer(renderer), m_window(window) 
{
}

Scene::~Scene()
{

}

void Scene::OnStart()
{
	for(auto i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->OnStart();
	}
}

void Scene::OnFixedIterate()
{
	for(auto i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->OnFixedIterate();
	}
}

void Scene::OnIterate()
{
	for(auto i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->OnIterate();
	}
}

void Scene::OnDraw(SDL_Renderer* renderer)
{
	for(auto i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->OnDraw(renderer);
	}
}

void Scene::OnEvent(SDL_Event* event)
{
	for(auto i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->OnEvent(event);
	}
}

void Scene::RegisterCollider(BoxCollider* rb)
{
	m_colliders.push_back(rb);
}

GameObject* Scene::AddGameObject(const std::string& name, const std::string& tag)
{
	this->m_gameObjects.push_back(std::make_unique<GameObject>(this, name, tag));

	return m_gameObjects[m_gameObjects.size()-1].get();
}

GameObject* Scene::GetGameObject(int index)
{
	if(index < 0 || index >= m_gameObjects.size()) return NULL;
	return this->m_gameObjects[index].get();
}

GameObject* Scene::GetGameObject(const std::string& name)
{
	int size = m_gameObjects.size();
	for(int i = 0; i < size; ++i)
	{
		if(m_gameObjects[i]->GetName() == name)
		{
			return m_gameObjects[i].get();
		}
	}

	return NULL;
}

SDL_Renderer* Scene::GetRenderer() const 
{
	return m_renderer;
}

SDL_Window* Scene::GetWindow() const
{
	return m_window;
}
const std::vector<BoxCollider*>& Scene::GetColliders() const
{
	return m_colliders;
};

void Scene::DEBUG_PrintGameObjAdd() const
{
	std::cout << "OBJ ADD: " << std::endl;
	for(auto i = 0; i < m_gameObjects.size(); ++i)
	{
		std::cout << m_gameObjects[i].get() << std::endl;
	}
}
