#include "CustomScene/GameScene/Goal.h"
#include "engine/GameObject.h"

Goal::Goal(GameObject* obj, GameManager* manager) : Component("Goal", obj), m_manager(manager) {};

void Goal::OnIterate() {};

std::unique_ptr<Component> Goal::copy()
{
	return std::make_unique<Goal>(gameObject, m_manager);
};

void Goal::OnTriggerEnter(GameObject* obj)
{
	if(obj->GetTag() == "Ball")
	{
		m_manager->Goal();
	}
};
