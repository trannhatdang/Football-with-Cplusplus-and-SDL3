#include "custom_scene.h"

static SDL_FRect playerSprRectArr[10];

void GenerateGameScene(const std::unique_ptr<Scene>& gameScene)
{
	gameScene->AddGameObject();
	auto tilemap_gb = gameScene->GetGameObject(0);

	std::vector<std::vector<int>> map = 
		{{6, 2, 2, 2, 2, 2, 7},
		{10, 0, 0, 0, 0, 0, 11},
		{4, 0, 0, 1, 0, 0, 5},
		{10, 0, 0, 0, 0, 0, 11},
		{9, 3, 3, 3, 3, 3, 8}};

	tilemap_gb->AddComponent(new Tilemap(tilemap_gb, gameScene->GetRenderer(), GetGrassSpriteSheet(), map, 160, 160));

	gameScene->AddGameObject();
	auto gb = gameScene->GetGameObject(1);
	static_cast<Transform*>(gb->GetTransform())->SetPosition({200, 300, -2});

	for(int i = 0; i < 10; ++i)
	{
		playerSprRectArr[i].x = (float)i*32;
		playerSprRectArr[i].y = 0;
		playerSprRectArr[i].w = 32;
		playerSprRectArr[i].h = 48;
	}

	gb->AddComponent(new SpriteRenderer(gb, gameScene->GetRenderer(), GetPlayerSpriteSheet(), playerSprRectArr[0], {0, 0, 32, 48}));
	gb->AddComponent(new Rigidbody(gb, true, 5));

	static_cast<Rigidbody*>(gb->GetComponent("Rigidbody"))->AddForce({10, 0, 0});

}	
