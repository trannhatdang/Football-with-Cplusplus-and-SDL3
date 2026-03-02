#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "engine/Components/Component.h"
#include "engine/Components/Rigidbody.h"
#include "engine/Components/Animator.h"
#include "Config.h"
#include "engine/DG_Time.h"
#include "engine/dg_vector.h"

class Movement: public Component
{
	private:
		SDL_Renderer* m_renderer;
		SDL_Texture* m_selected_arrow;
		SDL_Texture* m_unselected_arrow;
		float m_speed = 0.0f;

		float m_hort = 0.0f;
		float m_vert = 0.0f;
		bool m_playerControl = true;
		bool m_haveControl = false;
		bool m_cursor = false;
		bool m_playerOne = true;
	public:
		Movement(GameObject* obj, SDL_Renderer* renderer, float speed = 1.0f, bool haveControl = false, bool playerOne = true);
		~Movement();
		void OnIterate();
		void OnFixedIterate();
		void OnEvent(SDL_Event* event);
		void OnDraw(SDL_Renderer* renderer);
		std::unique_ptr<Component> copy();
		Vector3 GetOGPos() const;
		bool GetControl() const;
		bool GetCursor() const;
		bool GetHasBall(GameObject* ball) const;
		void SetControl();
		void SetCursor();
		void PlayerOneControls(SDL_Event* event);
		void PlayerTwoControls(SDL_Event* event);

		void SetBotControl();
		void SetDir(float hort = 0.0f, float vert = 0.0f);

};

#endif
