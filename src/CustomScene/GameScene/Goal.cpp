#include "CustomScene/GameScene/Goal.h"
#include "engine/GameObject.h"

Goal::Goal(GameObject* obj, GameManager* manager, int team) : Component("Goal", obj), m_manager(manager), m_team(team) {};

void Goal::OnIterate() {};

std::unique_ptr<Component> Goal::copy()
{
	return std::make_unique<Goal>(gameObject, m_manager, m_team);
};

void Goal::OnTriggerEnter(GameObject* obj)
{
	if(obj->GetTag() == "Ball")
	{
		m_manager->Goal(m_team);
	}
};
