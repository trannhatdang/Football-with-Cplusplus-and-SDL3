#include "CustomScene/GameScene/GameManager.h"
#include "engine/Scene.h"

GameManager::GameManager(GameObject* obj, Scene* scene, const GameState& state) : Component("GameManager", obj), m_scene(scene), m_gameState(state), m_recording(false)
{

}

void GameManager::OnStart()
{
	m_players = m_scene->GetGameObjectsWithTag("Player");
	m_controllers = m_scene->GetGameObjectsWithTag("Controller");
	m_ball = m_scene->GetGameObject("Ball");
	m_score = m_scene->GetGameObject("Score");
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
	for(auto player : m_players)
	{
		auto ogPos = player->GetTransform()->GetOGPosition();
		player->GetTransform()->SetPosition(ogPos);
		static_cast<Rigidbody*>(player->GetComponent("Rigidbody"))->Reset();
	}

	for(auto controller : m_controllers)
	{
		static_cast<Controller*>(controller->GetComponent("Controller"))->Reset();
	}

	auto ballPos = m_ball->GetTransform()->GetOGPosition();
	m_ball->GetTransform()->SetPosition(ballPos);
	static_cast<Rigidbody*>(m_ball->GetComponent("Rigidbody"))->Reset();

	static_cast<Font*>(m_score->GetComponent("Font"))->SetText(std::to_string(m_team1_score) + " : " + std::to_string(m_team2_score));
}

std::unique_ptr<Component> GameManager::copy()
{
	return std::make_unique<GameManager>(gameObject, m_scene, m_gameState);
}

GameState GameManager::GetState() const
{
	return m_gameState;
}

int GameManager::GetTeamOneScore() const
{
	return m_team1_score;
}

int GameManager::GetTeamTwoScore() const
{
	return m_team2_score;
}

bool GameManager::GetPaused() const
{
	return m_gameState == Paused;
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
