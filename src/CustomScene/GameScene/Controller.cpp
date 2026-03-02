#include "CustomScene/GameScene/Controller.h"
#include "engine/GameObject.h"

Controller::Controller(GameObject* obj, const std::vector<Movement*>& players, SDL_Keycode code) : Component("Controller", obj), m_players(players), m_key(code)
{
	if(m_players.size() != 0)
	{
		m_currPlayer = m_players[0];
		m_ogPlayer = m_currPlayer;
	}
	else
	{
		m_currPlayer = nullptr;
	}

	if(m_players.size() >= 1)
	{
		m_nextPlayer = FindNextPlayer(m_currPlayer);
		m_nextPlayer->SetCursor();
	}
	else
	{
		m_nextPlayer = nullptr;
	}
}

Movement* Controller::FindNextPlayer(Movement* player)
{
	Vector3 pos = player->GetGameObject()->GetTransform()->GetPosition();
	Movement* nextPlayer = nullptr;
	int min_dist = INT_MAX;

	for(auto it : m_players)
	{
		if(it == player) continue;

		int dist = (pos - it->GetGameObject()->GetTransform()->GetPosition()).magnitude();
		if(min_dist > dist)
		{
			nextPlayer = it;
			min_dist = dist;
		}
	}

	return nextPlayer;
}

void Controller::SwitchPlayer()
{
	m_nextPlayer->SetCursor();

	m_currPlayer->SetControl();
	m_currPlayer = m_nextPlayer;
	m_currPlayer->SetControl();

	m_nextPlayer = FindNextPlayer(m_currPlayer);

	m_nextPlayer->SetCursor();
}

void Controller::OnIterate()
{
	if(!m_currPlayer->GetControl())
	{
		m_currPlayer->SetControl();
	}

	auto next = FindNextPlayer(m_currPlayer);

	if(next != m_nextPlayer)
	{
		m_nextPlayer->SetCursor();
		m_nextPlayer = next;
		m_nextPlayer->SetCursor();
	}
}

void Controller::OnEvent(SDL_Event* event)
{
	if(event->type == SDL_EVENT_KEY_DOWN && event->key.down)
	{
		auto keyEvent = event->key;
		if(event->key.key == m_key)
		{
			this->SwitchPlayer();
		}
	}
}

void Controller::AddPlayer(Movement* move)
{
	m_players.push_back(move);
}

std::unique_ptr<Component> Controller::copy()
{
	return std::make_unique<Controller>(gameObject, m_players, m_key);
}

void Controller::Reset()
{
	m_currPlayer->SetControl();
	m_currPlayer = m_ogPlayer;
	m_currPlayer->SetControl();
}

Movement* Controller::GetCurrPlayer() const
{
	return m_currPlayer;
}

void Controller::SetBotControl()
{
	for(auto it : m_players)
	{
		it->SetBotControl();
	}
}

bool Controller::IsCurrClosestToPos(const Vector3& pos)
{
	auto dist = (m_currPlayer->GetGameObject()->GetTransform()->GetPosition() - pos).magnitude();
	for (auto it : m_players)
	{
		if (it == m_currPlayer) continue;

		auto new_pos = it->GetGameObject()->GetTransform()->GetPosition();
		auto new_dist = (new_pos - pos).magnitude();
		if (dist > new_dist)
		{
			return false;
		}
	}
	return true;
}
