#include <SDL3/SDL.h>
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include "engine/scene.h"
#include "config.h"
#include "custom_scene.h"

static SDL_Renderer* renderer = nullptr;
static SDL_Window* window = nullptr;
static std::unique_ptr<Scene> scenes[10];
static Scene* currScene;
static std::chrono::milliseconds frametime;
static std::chrono::time_point last_iterate_point = std::chrono::system_clock::now();
SDL_Texture* texture;
int texture_w, texture_h;

Vector3 CameraPos;

Vector3 GetCameraPos()
{
	return CameraPos;
}

static void SetCameraPos(Vector3 pos)
{
	CameraPos = pos;
}

static void ChangeScene(int index)
{
	currScene = scenes[index].get();
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char** argv)
{
	char windowCaption[5] = "game";

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	SDL_LoadPNG("lmao");
	
	if(!SDL_CreateWindowAndRenderer(windowCaption, GetWindowWidth(), GetWindowHeight(), SDL_WINDOW_RESIZABLE, &window, &renderer))
	{
		SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_SetRenderLogicalPresentation(renderer, GetWindowWidth(), GetWindowHeight(), SDL_LOGICAL_PRESENTATION_LETTERBOX);

	scenes[0] = std::make_unique<Scene>("IntroScene", &ChangeScene, renderer, window);
	scenes[1] = std::make_unique<Scene>("MenuScene", &ChangeScene, renderer, window);
	scenes[2] = std::make_unique<Scene>("GameScene", &ChangeScene, renderer, window);
	scenes[3] = std::make_unique<Scene>("OptionsScene", &ChangeScene, renderer, window);

	GenerateGameScene(scenes[2]);

	ChangeScene(2); //Straight into game scene

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	if(std::chrono::system_clock::now() - last_iterate_point > frametime)
	{
		currScene->OnFixedIterate();
		last_iterate_point = std::chrono::system_clock::now();
	}
	currScene->OnIterate();
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	currScene->OnDraw(renderer);
	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	if (event->type == SDL_EVENT_QUIT)
	{
		return SDL_APP_SUCCESS;
	}
	currScene->OnEvent(event);
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	SDL_DestroyTexture(texture);

}
