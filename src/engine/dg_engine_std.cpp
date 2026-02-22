#include "engine/dg_engine_std.h"

SDL_Texture* CreateTextureFromPNG(SDL_Renderer* renderer, const std::string& filepath)
{
	SDL_Surface* surface = SDL_LoadPNG(filepath.c_str());
	if(!surface)
	{
		SDL_Log("Could not create surface for texture creation: %s", SDL_GetError());
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if(!texture)
	{
		SDL_Log("Could not create texture: %s", SDL_GetError());
	}
	SDL_DestroySurface(surface);

	return texture;
}

void DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect viewport, SDL_FRect srcrect, SDL_FRect dstrect)
{
	SDL_SetRenderViewport(renderer, &viewport);
	SDL_RenderTexture(renderer, texture, &srcrect, &dstrect);
}
