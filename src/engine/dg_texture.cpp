#include "engine/DG_Texture.h"

DG_Texture::DG_Texture(SDL_Texture* texture) : m_texture(texture)
{
	
}

DG_Texture::~DG_Texture()
{
	SDL_DestroyTexture(m_texture);
}

SDL_Texture* DG_Texture::GetTexture() const
{
	return m_texture;
}