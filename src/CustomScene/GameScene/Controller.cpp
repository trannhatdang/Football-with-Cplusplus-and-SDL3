#include "CustomScene/GameScene/Controller.h"
#include "engine/GameObject.h"

Controller::Controller(GameObject* obj, const std::vector<Movement*>& players) : Component("Controller", obj), m_players(players)
{
	if(m_players.size() != 0)
	{
		m_currPlayer = m_players[0];
	}

	if(m_players.size() >= 1)
	{
		findNextPlayer(m_currPlayer);
	}
	else
	{
		m_nextPlayer = nullptr;
	}

}

Movement* Controller::findNextPlayer(Movement* player)
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

void Controller::switchPlayer()
{
	m_nextPlayer->SetCursor();

	m_currPlayer = m_nextPlayer;
	m_nextPlayer = findNextPlayer(m_currPlayer);

	m_nextPlayer->SetCursor();
}

void Controller::OnIterate()
{
	if(!m_currPlayer->GetControl())
	{
		m_currPlayer->SetControl();
	}
}

void Controller::OnEvent(SDL_Event* event)
{
	if(event->type == SDL_EVENT_KEY_DOWN && event->key.down)
	{
		auto keyEvent = event->key;
		if(event->key.key == SDLK_SPACE)
		{
			this->switchPlayer();
		}
	}
}

void Controller::AddPlayer(Movement* move)
{
	m_players.push_back(move);
}

std::unique_ptr<Component> Controller::copy()
{
	return std::make_unique<Controller>(gameObject, m_players);
}
