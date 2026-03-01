#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "engine/Components/Component.h"
#include "engine/Components/Font.h"
#include "CustomScene/GameScene/Movement.h"
#include "CustomScene/GameScene/Controller.h"

#include "engine/dg_time.h"

class Scene;
enum GameState {
	Playing,
	Paused,
	Goaled
};

class GameManager : public Component
{
	private:
		std::vector<GameObject*> m_players;
		std::vector<GameObject*> m_controllers;
		GameObject* m_ball = nullptr;
		GameObject* m_score = nullptr;
		Scene* m_scene;

		GameState m_gameState = Playing;
		int m_team1_score = 0;
		int m_team2_score = 0;

		bool m_recording = false;
		dg_time m_lastTime;
		std::chrono::time_point<std::chrono::milliseconds> m_last_recoreded_time;

		void reset();
	public:
		GameManager(GameObject* obj, Scene* scene, const GameState& state = Playing);
		void OnStart();
		void OnIterate();
		std::unique_ptr<Component> copy();
		GameState GetState() const;
		int GetTeamOneScore() const;
		int GetTeamTwoScore() const;
		bool GetPaused() const;
		void Goal(int team = 0);
};

#endif
