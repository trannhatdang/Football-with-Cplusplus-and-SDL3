#ifndef SPRITE_RENDERER_H_
#define SPRITE_RENDERER_H_

#include "engine/Components/Component.h"
#include "engine/dg_texture.h"

class SpriteRenderer : public Component
{
	private:
		SDL_Texture* m_texture;
		SDL_FRect m_srcrect;
		SDL_FRect m_dstrect;

		const std::string filepath;
		SDL_Renderer* renderer;
	public:
		SpriteRenderer(GameObject* gameObject, SDL_Renderer* renderer, const std::string& filepath, SDL_FRect srcrect, SDL_FRect dstrect);
		~SpriteRenderer();
		void OnStart();
		void OnIterate();
		void OnDraw(SDL_Renderer* renderer, Vector3 CameraPos);
		void OnEvent(SDL_Event* event);
		std::unique_ptr<Component> copy();
};

#endif
