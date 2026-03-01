#ifndef DG_ENGINE_STD_
#define DG_ENGINE_STD_

#include <vector>
#include <memory>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <SDL3/SDL.h>
#include "dg_vector.h"

const int ON_COLLISION_ENTER_EVENT = SDL_RegisterEvents(1);
const int BOX_POS_EVENT = SDL_RegisterEvents(1);

SDL_Texture* CreateTextureFromPNG(SDL_Renderer* renderer, const std::string& filepath);
void DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect viewport, SDL_FRect srcrect, SDL_FRect dstrect);

#endif
