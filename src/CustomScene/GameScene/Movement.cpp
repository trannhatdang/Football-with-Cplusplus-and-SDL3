#include "CustomScene/GameScene/Movement.h"
#include "engine/GameObject.h"

Movement::Movement(GameObject* obj, float speed, bool haveControl, bool playerOne) : Component("Movement", obj), m_speed(speed), m_haveControl(haveControl), m_playerOne(playerOne)
{

}

Movement::~Movement()
{

}

void Movement::OnIterate()
{
	if(!m_haveControl) return;

	auto rb = static_cast<Rigidbody*>(gameObject->GetComponent("Rigidbody"));
	auto transform = gameObject->GetTransform();
	Vector3f dir = {m_vert, m_hort, 0.0f};
	Vector3 newDir = dir * DGTime_deltaTime() * m_speed;

	rb->MovePosition(transform->GetPosition() + newDir);
}

void Movement::OnEvent(SDL_Event* event)
{
	if(m_playerOne && m_haveControl)
	{
		PlayerOneControls(event);
	}
	else if(!m_playerOne && m_haveControl)
	{
		PlayerTwoControls(event);
	}
}

void Movement::SetControl()
{
	m_haveControl = !m_haveControl;
}

void Movement::PlayerOneControls(SDL_Event* event)
{
	if(event->type == SDL_EVENT_KEY_DOWN)
	{
		auto keyEvent = event->key;
		if(keyEvent.down)
		{
			if(keyEvent.key == SDLK_W)
			{
				m_hort = -1.0f;
			}

			if(keyEvent.key == SDLK_A)
			{
				m_vert = -1.0f;
			}

			if(keyEvent.key == SDLK_D)
			{
				m_vert = 1.0f;
			}

			if(keyEvent.key == SDLK_S)
			{
				m_hort = 1.0f;
			}
		}
	}
	else if(event->type == SDL_EVENT_KEY_UP)
	{
		auto keyEvent = event->key;
		if(!keyEvent.down)
		{
			if(keyEvent.key == SDLK_W)
			{
				m_hort = m_hort < 0 ? 0.0f : m_hort;
			}

			if(keyEvent.key == SDLK_A)
			{
				m_vert = m_vert < 0 ? 0.0f : m_vert;
			}

			if(keyEvent.key == SDLK_D)
			{
				m_vert = m_vert > 0 ? 0.0f : m_vert;
			}

			if(keyEvent.key == SDLK_S)
			{
				m_hort = m_hort > 0 ? 0.0f : m_hort;
			}

		}
	}

}

void Movement::PlayerTwoControls(SDL_Event* event)
{
	if(event->type == SDL_EVENT_KEY_DOWN)
	{
		auto keyEvent = event->key;
		if(keyEvent.down)
		{
			if(keyEvent.key == SDLK_UP)
			{
				m_hort = -1.0f;
			}

			if(keyEvent.key == SDLK_LEFT)
			{
				m_vert = -1.0f;
			}

			if(keyEvent.key == SDLK_RIGHT)
			{
				m_vert = 1.0f;
			}

			if(keyEvent.key == SDLK_DOWN)
			{
				m_hort = 1.0f;
			}
		}
	}
	else if(event->type == SDL_EVENT_KEY_UP)
	{
		auto keyEvent = event->key;
		if(!keyEvent.down)
		{
			if(keyEvent.key == SDLK_UP)
			{
				m_hort = m_hort < 0 ? 0.0f : m_hort;
			}

			if(keyEvent.key == SDLK_LEFT)
			{
				m_vert = m_vert < 0 ? 0.0f : m_vert;
			}

			if(keyEvent.key == SDLK_RIGHT)
			{
				m_vert = m_vert > 0 ? 0.0f : m_vert;
			}

			if(keyEvent.key == SDLK_DOWN)
			{
				m_hort = m_hort > 0 ? 0.0f : m_hort;
			}

		}
	}

}
std::unique_ptr<Component> Movement::copy()
{
	return std::make_unique<Movement>(gameObject);
}
