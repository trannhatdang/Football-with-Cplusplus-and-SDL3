#include "engine/Components/Component.h"

Component::Component(const std::string& name, GameObject* gameObject) : m_name(name), gameObject(gameObject)
{

}

Component::~Component()
{

}

std::string Component::GetName() const
{
	return m_name;
}


void Component::OnStart()
{

};

void Component::OnFixedIterate()
{

};

void Component::OnDraw(SDL_Renderer* renderer, Vector3 CameraPos)
{

};

void Component::OnEvent(SDL_Event* event)
{

};
