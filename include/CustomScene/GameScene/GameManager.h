#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "engine/Components/Component.h"
#include "engine/dg_time.h"

enum GameState {
	Playing,
	Paused,
	Goaled
};

class GameManager : public Component
{
	private:
		GameState m_gameState = Playing;
		int m_team1_score = 0;
		int m_team2_score = 0;

		bool m_recording = false;
		dg_time m_lastTime;
		std::chrono::time_point<std::chrono::milliseconds> m_last_recoreded_time;

		void reset();
	public:
		GameManager(GameObject* obj, const GameState& state = Playing);
		void OnIterate();
		std::unique_ptr<Component> copy();
		GameState GetState() const;
		int GetTeamOneScore() const;
		int GetTeamTwoScore() const;
		void Goal(int team = 0);
};

#endif
