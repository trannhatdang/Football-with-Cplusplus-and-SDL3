#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "engine/Components/Component.h"

enum GameState {
	Playing,
	Paused,
	Goal
};

class GameManager : public Component
{
	private:
		GameState m_game_state = Playing;
	public:
		GameManager(GameObject* obj);
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
