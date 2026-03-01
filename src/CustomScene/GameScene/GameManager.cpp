#include "CustomScene/GameScene/GameManager.h"

GameManager::GameManager(GameObject* obj, const GameState& state) : Component("GameManager", obj), m_gameState(state), m_recording(false)
{

}

void GameManager::OnIterate()
{
	if(m_gameState == Goaled)
	{
		if(!m_recording)
		{
			m_lastTime = std::chrono::system_clock::now();
			m_recording = true;
			return;
		}

		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

		if(std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastTime).count() > 3000)
		{
			m_recording = false;
			m_gameState = Playing;

			reset();
		}
	}
	else if(m_gameState == Paused)
	{

	}
	else
	{

	}
}

void GameManager::reset()
{

}

std::unique_ptr<Component> GameManager::copy()
{
	return std::make_unique<GameManager>(gameObject);
}

GameState GameManager::GetState() const
{
	return m_gameState;
}

void GameManager::Goal(int team)
{
	if(m_gameState != Playing) return;

	m_gameState = Goaled;

	if(team == 0)
	{
		m_team1_score++;
	}
	else if(team == 1)
	{
		m_team2_score++;
	}
}

int GameManager::GetTeamOneScore() const
{
	return m_team1_score;
}

int GameManager::GetTeamTwoScore() const
{
	return m_team2_score;
}
