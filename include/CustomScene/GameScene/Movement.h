#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "engine/Components/Component.h"
#include "engine/Components/Rigidbody.h"
#include "engine/Components/SpriteRenderer.h"
#include "Config.h"
#include "engine/DG_Time.h"
#include "engine/dg_vector.h"

class Movement: public Component
{
	private:
		float m_speed = 0.0f;
		SDL_Texture* m_selected_arrow;
		SDL_Texture* m_unselected_arrow;

		float m_hort = 0.0f;
		float m_vert = 0.0f;
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
		bool GetControl() const;
		void SetControl();
		bool GetCursor() const;
		void SetCursor();
		void PlayerOneControls(SDL_Event* event);
		void PlayerTwoControls(SDL_Event* event);
		std::unique_ptr<Component> copy();
};

#endif
