#include "engine/Components/SpriteRenderer.h"
#include "engine/GameObject.h"

SpriteRenderer::SpriteRenderer(GameObject* gameObject, SDL_Renderer* renderer, const std::string& filepath, SDL_FRect srcrect, SDL_FRect dstrect) : Component("SpriteRenderer", gameObject), m_srcrect(srcrect), m_dstrect(dstrect), filepath(filepath), renderer(renderer)
{
	SDL_Surface* surface = SDL_LoadPNG(filepath.c_str());
	if(!surface)
	{
		SDL_Log("Could not create surface for texture creation: %s", SDL_GetError());
	}

	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!m_texture)
	{
		SDL_Log("Could not create texture: %s", SDL_GetError());
	}
	SDL_DestroySurface(surface);
}

SpriteRenderer::~SpriteRenderer() 
{
	SDL_DestroyTexture(m_texture);
}

void SpriteRenderer::OnStart()
{

}

void SpriteRenderer::OnIterate() 
{

}

void SpriteRenderer::OnDraw(SDL_Renderer* renderer, Vector3 CameraPos)
{
	//ugly but works, kinda, i'm not managing that!
	Vector3 pos = static_cast<Transform*>(this->gameObject->GetTransform())->GetPosition();
	SDL_Rect viewport;
	//god what would happen if we go 3d?
	viewport.x = pos.x;
	viewport.y = pos.y;
	viewport.w = m_texture->w;
	viewport.h = m_texture->h;

	SDL_SetRenderViewport(renderer, &viewport);
	SDL_RenderTexture(renderer, m_texture, &m_srcrect, &m_dstrect);
}

void SpriteRenderer::OnEvent(SDL_Event* event) 
{

}

std::unique_ptr<Component> SpriteRenderer::copy()
{
	return std::make_unique<SpriteRenderer>(gameObject, renderer, filepath, m_srcrect, m_dstrect);
}
