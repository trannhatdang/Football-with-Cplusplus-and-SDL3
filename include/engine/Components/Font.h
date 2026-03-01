#ifndef FONT_H_
#define FONT_H_

#include "Component.h"
#include <SDL3_ttf/SDL_ttf.h>

class Font : public Component
{
	private:
		TTF_Font* m_font;
		SDL_Texture* m_texture;
		SDL_Renderer* m_renderer;

		int m_width;
		int m_height;

		std::string m_filepath = "";
		std::string m_text = "";

		void createTexture();
	public:
		Font(GameObject* obj, SDL_Renderer* renderer, const std::string& filepath);
		~Font();
		void OnIterate();
		void OnDraw(SDL_Renderer* renderer);
		std::unique_ptr<Component> copy();
		void SetText(const std::string& txt);
};

#endif
