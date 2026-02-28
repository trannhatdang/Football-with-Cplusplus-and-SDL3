#include "CustomScene/GameScene/Goal.h"


Goal::Goal(GameObject* obj) : Component("Goal", obj) {};

void Goal::OnIterate() {};

std::unique_ptr<Component> Goal::copy()
{
	return std::make_unique<Goal>(gameObject);
};

void Goal::OnTriggerEnter()
{

};
