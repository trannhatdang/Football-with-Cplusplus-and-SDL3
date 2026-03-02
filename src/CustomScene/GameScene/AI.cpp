#include "CustomScene/GameScene/AI.h"

AI::AI(GameObject* obj, GameManager* manager, Controller* ctrl) : Component("AI", obj), m_manager(manager), m_ctrl(ctrl)
{

}

void AI::OnIterate()
{
	if(!m_activated) return;

	GameObject* ball = m_manager->GetBall();
	Movement* currPlayer = m_ctrl->GetCurrPlayer();

	Vector3 ball_pos = ball->GetTransform()->GetPosition();
	Vector3 goal_pos = m_manager->GetGoalPos(1);
	Vector3 player_pos = currPlayer->GetGameObject()->GetTransform()->GetPosition();

	if(currPlayer->GetHasBall(ball))
	{
		Vector3 dir = goal_pos - player_pos;
		Vector3f unit_vector = Vector3f_GetUnitVector(dir);

		currPlayer->SetDir(std::round(unit_vector.x), std::round(unit_vector.y));
	}
	else
	{
		Vector3 dir = ball_pos - player_pos;
		Vector3f unit_vector = Vector3f_GetUnitVector(dir);

		//std::cout << std::round(unit_vector.x) << ", " <<  std::round(unit_vector.y) << std::endl;

		currPlayer->SetDir(std::round(unit_vector.x), std::round(unit_vector.y));
	}

	if(!m_ctrl->IsCurrClosestToPos(ball_pos))
	{
		m_ctrl->SwitchPlayer();
	}
}

void AI::OnEvent(SDL_Event* event)
{
	if(event->type == SDL_EVENT_KEY_DOWN && event->key.down)
	{
		auto keyEvent = event->key;
		if(keyEvent.key == SDLK_T)
		{
			m_ctrl->SetBotControl();
			m_activated = !m_activated;
		}
	}
}

std::unique_ptr<Component> AI::copy()
{
	return std::make_unique<AI>(gameObject, m_manager, m_ctrl);
}
