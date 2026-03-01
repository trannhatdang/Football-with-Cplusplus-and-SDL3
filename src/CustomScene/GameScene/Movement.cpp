#include "CustomScene/GameScene/Movement.h"
#include "engine/GameObject.h"

Movement::Movement(GameObject* obj, SDL_Renderer* renderer, float speed, bool haveControl, bool playerOne) : Component("Movement", obj), m_speed(speed), m_haveControl(haveControl), m_playerOne(playerOne)
{
	m_selected_arrow = CreateTextureFromPNG(renderer, GetSelectedArrowSprite());
	m_unselected_arrow = CreateTextureFromPNG(renderer, GetUnselectedArrowSprite());
}

Movement::~Movement()
{

}

void Movement::OnFixedIterate()
{
	if(!m_haveControl) return;

	auto rb = static_cast<Rigidbody*>(gameObject->GetComponent("Rigidbody"));
	auto transform = gameObject->GetTransform();
	Vector3f dir = {m_vert, m_hort, 0.0f};
	Vector3f new_dir = dir * m_speed;
	Vector3 new_dir_int =
		Vector3(new_dir.x > 0 ? std::ceil(new_dir.x) : std::floor(new_dir.x),
			new_dir.y > 0 ? std::ceil(new_dir.y) : std::floor(new_dir.y),
			new_dir.z > 0 ? std::ceil(new_dir.z) : std::floor(new_dir.z));

	//std::cout << DGTime_deltaTime() << std::endl;
	//std::cout << new_dir << std::endl;
	//rb->MovePosition(transform->GetPosition() + new_dir_int);
	rb->AddForce(new_dir);
}

void Movement::OnIterate()
{

}

void Movement::OnEvent(SDL_Event* event)
{
	if (!m_haveControl) return;

	if(m_playerOne)
	{
		PlayerOneControls(event);
	}
	else
	{
		PlayerTwoControls(event);
	}
}

void Movement::OnDraw(SDL_Renderer* renderer)
{
	SDL_FRect dstrect = static_cast<SpriteRenderer*>(gameObject->GetComponent("SpriteRenderer"))->GetDstRect();
	Vector3 pos = gameObject->GetTransform()->GetPosition() + Vector3(dstrect.w/2, -20, 0);

	SDL_FRect viewport;
	viewport.x = pos.x;
	viewport.y = pos.y;
	viewport.w = 10;
	viewport.h = 10;

	DrawTexture(renderer, m_texture, viewport, m_srcrect, m_dstrect);
}

bool Movement::GetControl() const
{
	return m_haveControl;
}

void Movement::SetControl()
{
	m_haveControl = !m_haveControl;
}

bool Movement::GetCursor() const
{
	return m_cursor;
}

void Movement::SetCursor()
{
	m_cursor = !m_cursor;
}

void Movement::PlayerOneControls(SDL_Event* event)
{
	if(event->type == SDL_EVENT_KEY_DOWN && event->key.down)
	{
		auto keyEvent = event->key;
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
	else if(event->type == SDL_EVENT_KEY_UP && !event->key.down)
	{
		auto keyEvent = event->key;
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

void Movement::PlayerTwoControls(SDL_Event* event)
{
	if(event->type == SDL_EVENT_KEY_DOWN && event->key.down)
	{
		auto keyEvent = event->key;
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
	else if(event->type == SDL_EVENT_KEY_UP && !event->key.down)
	{
		auto keyEvent = event->key;
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
std::unique_ptr<Component> Movement::copy()
{
	return std::make_unique<Movement>(gameObject);
}
