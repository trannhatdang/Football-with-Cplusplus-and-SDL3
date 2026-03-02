#include "CustomScene/GameScene/GameManager.h"
#include "engine/Scene.h"

GameManager::GameManager(GameObject* obj, Scene* scene, const GameState& state) : Component("GameManager", obj), m_scene(scene), m_gameState(state), m_recording(false)
{

}

void GameManager::reset(int keep_score)
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
	static_cast<Wind*>(m_ball->GetComponent("Wind"))->Reset();
	static_cast<Font*>(m_wind_speed->GetComponent("Font"))->SetText("(" + std::to_string(0.0f) + ", " + std::to_string(0.0f) + ")");

	if(!keep_score)
	{
		m_team1_score = 0;
		m_team2_score = 0;
	}

	static_cast<Font*>(m_score->GetComponent("Font"))->SetText(std::to_string(m_team1_score) + " : " + std::to_string(m_team2_score));
}

void GameManager::OnStart()
{
	m_players = m_scene->GetGameObjectsWithTag("Player");
	m_controllers = m_scene->GetGameObjectsWithTag("Controller");
	m_ball = m_scene->GetGameObject("Ball");
	m_score = m_scene->GetGameObject("Score");
	m_goal_0 = m_scene->GetGameObject("Goal1");
	m_goal_1 = m_scene->GetGameObject("Goal2");
	m_wind_speed = m_scene->GetGameObject("WindSpeed");
}

void GameManager::OnIterate()
{
	if(m_gameState == Goaled)
	{
		static_cast<Font*>(m_score->GetComponent("Font"))->SetText(std::to_string(m_team1_score) + " : " + std::to_string(m_team2_score));
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

			reset(true);
		}
	}
	else if(m_gameState == Paused)
	{

	}
	else
	{

	}

}

void GameManager::changeWindSpeed()
{
	auto wind = (Wind*)m_ball->GetComponent("Wind");
	
	float new_x = (float)(rand() % 4 - 2);
	float new_y = (float)(rand() % 4 - 2);
	float new_z = (float)(rand() % 4 - 2);
	wind->SetWindSpeed({ new_x, new_y, new_z });
	if(m_wind_speed)
	{
		static_cast<Font*>(m_wind_speed->GetComponent("Font"))->SetText("(" + std::to_string(new_x) + ", " + std::to_string(new_y) + ")");
	}
}

void GameManager::OnEvent(SDL_Event* event)
{
	if(event->type == SDL_EVENT_KEY_DOWN && event->key.down)
	{
		auto keyEvent = event->key;
		if(keyEvent.key == SDLK_R)
		{
			reset(false);
		}
		else if(keyEvent.key == SDLK_C)
		{
			changeWindSpeed();
		}
	}
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

GameObject* GameManager::GetBall() const
{
	return m_ball;
}

Vector3 GameManager::GetGoalPos(int team) const
{
	if(team)
	{
		return m_goal_0->GetTransform()->GetPosition() + Vector3(40, 80, 0);
	}
	else
	{
		return m_goal_1->GetTransform()->GetPosition() + Vector3(40, 80, 0);
	}

}
