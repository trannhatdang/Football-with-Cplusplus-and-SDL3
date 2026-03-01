#include "engine/Components/Font.h"
#include "engine/GameObject.h"

Font::Font(GameObject* obj, SDL_Renderer* renderer, const std::string& filepath) : Component("Font", obj), m_renderer(renderer), m_filepath(filepath)
{
	m_font = TTF_OpenFont(filepath.c_str(), 28);
}

Font::~Font()
{
	TTF_CloseFont(m_font);
}

void Font::createTexture()
{
	SDL_DestroyTexture(m_texture);
	SDL_Surface* textSurface = TTF_RenderText_Solid( m_font, m_text.c_str(), m_text.length(), {0, 0, 0, 255});

	if(!textSurface)
	{
		std::cout << gameObject->GetName() << ": couldn't create textSurface for font" << std::endl;
	}

	m_texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
	m_width = textSurface->w;
	m_height = textSurface->h;

	SDL_DestroySurface(textSurface);
}

void Font::OnIterate()
{

}

void Font::OnDraw(SDL_Renderer* renderer)
{
	Vector3 pos = static_cast<Transform*>(this->gameObject->GetTransform())->GetPosition();

	SDL_FRect m_srcrect;
	m_srcrect.x = 0;
	m_srcrect.y = 0;
	m_srcrect.w = m_width;
	m_srcrect.h = m_height;

	SDL_FRect m_dstrect;
	m_dstrect.x = 0;
	m_dstrect.y = 0;
	m_dstrect.w = m_width;
	m_dstrect.h = m_height;

	SDL_Rect viewport;
	viewport.x = pos.x;
	viewport.y = pos.y;
	viewport.w = m_width;
	viewport.h = m_width;

	DrawTexture(renderer, m_texture, viewport, m_srcrect, m_dstrect);
}

std::unique_ptr<Component> Font::copy()
{
	return std::make_unique<Font>(gameObject, m_renderer, m_filepath);
}

void Font::SetText(const std::string& txt)
{
	m_text = txt;
	createTexture();
}
