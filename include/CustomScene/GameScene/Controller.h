#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "engine/Components/Component.h"
#include "Movement.h"

class Controller : public Component
{
	private:
		std::vector<Movement*> m_players;
		Movement* m_ogPlayer;
		Movement* m_currPlayer;
		Movement* m_nextPlayer;
		SDL_Keycode m_key;

		void switchPlayer();
		Movement* findNextPlayer(Movement* player);
	public:
		Controller(GameObject* obj, const std::vector<Movement*>& players, SDL_Keycode key);
		void OnIterate();
		void OnEvent(SDL_Event* event);
		std::unique_ptr<Component> copy();
		void AddPlayer(Movement* move);
		void Reset();
};

#endif
