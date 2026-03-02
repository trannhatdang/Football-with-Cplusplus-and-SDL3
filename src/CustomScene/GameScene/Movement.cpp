#include "CustomScene/GameScene/Movement.h"
#include "engine/GameObject.h"

Movement::Movement(GameObject* obj, SDL_Renderer* renderer, float speed, bool haveControl, bool playerOne) : Component("Movement", obj), m_renderer(renderer), m_speed(speed), m_haveControl(haveControl), m_playerOne(playerOne)
{
	m_selected_arrow = CreateTextureFromPNG(renderer, GetSelectedArrowSprite());
	m_unselected_arrow = CreateTextureFromPNG(renderer, GetUnselectedArrowSprite());

	m_cursor = false;
}

Movement::~Movement()
{
	SDL_DestroyTexture(m_selected_arrow);
	SDL_DestroyTexture(m_unselected_arrow);
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

	if(!m_playerControl)
	{
		std::cout << dir << std::endl;
		std::cout << new_dir_int << std::endl;
	}
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
	if (!m_playerControl) return;

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
	if(!m_cursor && !m_haveControl) return;
	
	auto anim = static_cast<Animator*>(gameObject->GetComponent("Animator"));
	if (!anim) return;

	SDL_FRect anim_dstrect = anim->GetDstRect();
	Vector3 pos = gameObject->GetTransform()->GetPosition() + Vector3(anim_dstrect.w/2 - 5, -20, 0);

	SDL_Texture* texture = m_haveControl ? m_selected_arrow : m_unselected_arrow;

	SDL_Rect viewport;
	viewport.x = pos.x;
	viewport.y = pos.y;
	viewport.w = 10;
	viewport.h = 10;

	SDL_FRect srcrect;
	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 10;
	srcrect.h = 10;

	SDL_FRect dstrect;
	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = 10;
	dstrect.h = 10;

	DrawTexture(renderer, texture, viewport, srcrect, dstrect);
}

bool Movement::GetControl() const
{
	return m_haveControl;
}

bool Movement::GetCursor() const
{
	return m_cursor;
}

bool Movement::GetHasBall(GameObject* obj) const
{
	if(!obj) return false;

	auto ball_pos = obj->GetTransform()->GetPosition();
	auto pos = gameObject->GetTransform()->GetPosition();

	auto dist = ball_pos - pos;

	if(dist.magnitude() < 50)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Movement::SetControl()
{
	m_haveControl = !m_haveControl;
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
	return std::make_unique<Movement>(gameObject, m_renderer, m_speed, m_haveControl, m_playerOne);
}

void Movement::SetBotControl()
{
	m_playerControl = !m_playerControl;
}

void Movement::SetDir(float vert, float hort)
{
	if(m_playerControl) return;

	m_hort = hort;
	m_vert = vert;
}
