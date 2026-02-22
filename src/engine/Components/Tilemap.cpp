#include "engine/Components/Tilemap.h"
#include "engine/GameObject.h"

Tilemap::Tilemap(GameObject* obj, SDL_Renderer* renderer, const std::string& filepath, const std::vector<std::vector<int>>& map, int width, int height, int scale) : Component("Tilemap", obj), m_renderer(renderer), m_map(map), m_width(width), m_height(height), m_scale(scale)
{
	m_texture = CreateTextureFromPNG(renderer, filepath);

	m_srcrect.x = 0;
	m_srcrect.y = 0;
	m_srcrect.w = 16;
	m_srcrect.h = 16;

	m_dstrect.x = 0;
	m_dstrect.y = 0;
	m_dstrect.w = 160;
	m_dstrect.h = 160;
}

Tilemap::~Tilemap()
{
	SDL_DestroyTexture(m_texture);
}

void Tilemap::OnIterate()
{

}

void Tilemap::OnDraw(SDL_Renderer* renderer)
{
	for(auto i = 0; i < m_map.size(); ++i)
	{
		for(auto j = 0; j < m_map[i].size(); ++j)
		{
			SDL_Rect viewport;
			viewport.x = j * m_width * m_scale;
			viewport.y = i * m_height * m_scale;
			viewport.w = m_width * m_scale;
			viewport.h = m_height * m_scale;

			SDL_FRect srcrect;
			srcrect.x = m_map[i][j] * m_width;
			srcrect.y = 0;
			srcrect.w = m_width;
			srcrect.h = m_height;

			SDL_FRect dstrect;
			dstrect.x = 0;
			dstrect.y = 0;
			dstrect.w = m_width * m_scale;
			dstrect.h = m_height * m_scale;

			DrawTexture(renderer, m_texture, viewport, srcrect, dstrect);
		}
	}
}

std::unique_ptr<Component> Tilemap::copy()
{
	return std::make_unique<Tilemap>(this->gameObject, this->m_renderer, this->m_filepath, this->m_map, this->m_width, this->m_height);
}
