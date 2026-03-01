#ifndef GOAL_H_
#define GOAL_H_

#include "engine/Components/Component.h"
#include "GameManager.h"

class Goal : public Component
{
	private:
		GameManager* m_manager;
	public:
		Goal(GameObject* obj, GameManager* manager);
		void OnIterate();
		std::unique_ptr<Component> copy();
		void OnTriggerEnter(GameObject* obj);
};

#endif
