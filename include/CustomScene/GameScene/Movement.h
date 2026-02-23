#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "engine/Components/Component.h"
#include "engine/Components/Rigidbody.h"
#include "engine/DG_Time.h"
#include "engine/dg_vector.h"

class Movement: public Component
{
	private:
		float m_speed = 0.0f;

		float m_hort = 0.0f;
		float m_vert = 0.0f;
		bool m_haveControl = false;
		bool m_playerOne = true;
		
	public:
		Movement(GameObject* obj, float speed = 1.0f, bool haveControl = false, bool playerOne = true);
		~Movement();
		void OnIterate();
		void OnEvent(SDL_Event* event);
		void SetControl();
		void PlayerOneControls(SDL_Event* event);
		void PlayerTwoControls(SDL_Event* event);
		std::unique_ptr<Component> copy();
};

#endif
