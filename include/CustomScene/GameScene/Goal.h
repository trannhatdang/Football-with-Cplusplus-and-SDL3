#ifndef GOAL_H_
#define GOAL_H_

#include "engine/Components/Component.h"

class Goal : public Component
{
	public:
		Goal(GameObject* obj);
		void OnIterate();
		std::unique_ptr<Component> copy();
		void OnTriggerEnter();
};

#endif
