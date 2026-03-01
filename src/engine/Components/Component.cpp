#include "engine/Components/Component.h"

Component::Component(const std::string& name, GameObject* gameObject) : m_name(name), gameObject(gameObject)
{

}

Component::~Component()
{

}

void Component::OnStart()
{

}

void Component::OnFixedIterate()
{

}

void Component::OnDraw(SDL_Renderer* renderer)
{

}

void Component::OnEvent(SDL_Event* event)
{

}

void Component::OnCollisionEnter(GameObject* other)
{

}

void Component::OnTriggerEnter(GameObject* other)
{

}

GameObject* Component::GetGameObject() const
{
	return gameObject;
}

std::string Component::GetName() const
{
	return m_name;
}
