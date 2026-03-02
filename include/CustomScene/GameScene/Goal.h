#ifndef GOAL_H_
#define GOAL_H_

#include "engine/Components/Component.h"
#include "GameManager.h"

class Goal : public Component
{
	private:
		GameManager* m_manager;
		int m_team = 0;
	public:
		Goal(GameObject* obj, GameManager* manager, int m_team = 0);
		void OnIterate();
		std::unique_ptr<Component> copy();
		void OnTriggerEnter(GameObject* obj);
};

#endif
