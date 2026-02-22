#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "Component.h"
#include "engine/dg_texture.h"
#include "engine/main.h"

class Tilemap : public Component
{
	private:
		SDL_Texture* m_texture;
		SDL_Renderer* m_renderer;
		int m_width = 10;
		int m_height = 10;
		int m_scale = 10;
		std::string m_filepath;
		std::vector<std::vector<int>> m_map;

		SDL_FRect m_srcrect;
		SDL_FRect m_dstrect;
	public:
		Tilemap(GameObject* obj, SDL_Renderer* renderer, const std::string& filepath, const std::vector<std::vector<int>>& map, int width = 10, int height = 10, int scale = 1);
		~Tilemap();
		void OnIterate();
		void OnDraw(SDL_Renderer* renderer);
		std::unique_ptr<Component> copy();
};

#endif
