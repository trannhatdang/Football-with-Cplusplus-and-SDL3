#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "engine/Components/Component.h"
#include "Movement.h"

class Controller : public Component
{
	private:
		bool m_playerControl = false;

		std::vector<Movement*> m_players;
		Movement* m_ogPlayer;
		Movement* m_currPlayer;
		Movement* m_nextPlayer;
		SDL_Keycode m_key;
	public:
		Controller(GameObject* obj, const std::vector<Movement*>& players, SDL_Keycode key);
		void OnIterate();
		void OnEvent(SDL_Event* event);
		std::unique_ptr<Component> copy();
		void AddPlayer(Movement* move);
		void Reset();

		void SwitchPlayer();
		Movement* FindNextPlayer(Movement* player);
		Movement* GetCurrPlayer() const;

		void SetBotControl();
		bool IsCurrClosestToPos(const Vector3& pos);
};

#endif
