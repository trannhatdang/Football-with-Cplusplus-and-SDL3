#include "CustomScene/GameScene/GameManager.h"

GameManager::GameManager(GameObject* obj) : Component("GameManager", obj)
{

}

void GameManager::OnIterate()
{

}

std::unique_ptr<Component> GameManager::copy()
{
	return std::make_unique<GameManager>(gameObject);
}
