#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "engine/Components/Component.h"
#include "Movement.h"

class Controller : public Component
{
	private:
		std::vector<Movement*> m_players;
		Movement* m_currPlayer;
		Movement* m_nextPlayer;

		void switchPlayer();
		Movement* findNextPlayer(Movement* player);
	public:
		Controller(GameObject* obj, const std::vector<Movement*>& players);
		void OnIterate();
		void OnEvent(SDL_Event* event);
		void AddPlayer(Movement* move);
		std::unique_ptr<Component> copy();
};

#endif
