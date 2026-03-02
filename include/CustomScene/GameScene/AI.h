#ifndef AI_H_
#define AI_H_

#include "engine/Components/Component.h"
#include "GameManager.h"

class AI : public Component
{
	private:
		GameManager* m_manager;
		Controller* m_ctrl;
		bool m_activated = false;
	public:
		AI(GameObject* obj, GameManager* manager, Controller* ctrl);
		void OnIterate();
		void OnEvent(SDL_Event* event);
		std::unique_ptr<Component> copy();
};

#endif
