#include "CustomScene/GameScene/GameScene.h"

static SDL_FRect playerSprRect = {0, 0, 80, 80};
static SDL_FRect ballSprRect = {0, 0, 48, 48};

void GenerateGameScene(const std::unique_ptr<Scene>& gameScene)
{
	gameScene->AddGameObject("Tilemap", "Tilemap");
	auto tilemap_gb = gameScene->GetGameObject(0);

	std::vector<std::vector<int>> map = 
		{{6, 2, 2, 2, 2, 2, 7},
		{10, 0, 0, 0, 0, 0, 11},
		{4, 0, 0, 1, 0, 0, 5},
		{10, 0, 0, 0, 0, 0, 11},
		{9, 3, 3, 3, 3, 3, 8}};

	tilemap_gb->AddComponent(new Tilemap(tilemap_gb, gameScene->GetRenderer(), GetGrassSpriteSheet(), map, 160, 160));

	gameScene->AddGameObject("Player1", "Player");
	auto gb = gameScene->GetGameObject(1);
	static_cast<Transform*>(gb->GetTransform())->SetPosition({100, 300, -2});
	gb->AddComponent(new SpriteRenderer(gb, gameScene->GetRenderer(), GetPlayerSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	gb->AddComponent(new Rigidbody(gb, true, 5));
	gb->AddComponent(new BoxCollider(gb, {40, 40}));
	gb->AddComponent(new Movement(gb, 0.01f, true, true));

	gameScene->AddGameObject("Player2", "Player");
	auto gb2 = gameScene->GetGameObject(2);
	static_cast<Transform*>(gb2->GetTransform())->SetPosition({1000, 300, -2});
	gb2->AddComponent(new SpriteRenderer(gb2, gameScene->GetRenderer(), GetPlayerTwoSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	gb2->AddComponent(new Rigidbody(gb2, true, 5));
	gb2->AddComponent(new BoxCollider(gb2, {40, 40}));
	gb2->AddComponent(new Movement(gb2, 0.01f, true, false));

	gameScene->AddGameObject("Ball", "Ball");
	auto ball = gameScene->GetGameObject(3);
	static_cast<Transform*>(ball->GetTransform())->SetPosition({560, 400, -2});
	ball->AddComponent(new SpriteRenderer(ball, gameScene->GetRenderer(), GetBallSprite(), ballSprRect, ballSprRect));
	ball->AddComponent(new Rigidbody(ball, true, 5));
	ball->AddComponent(new BoxCollider(ball, {48, 48}));

	gameScene->AddGameObject("Ball2", "Ball");
	auto ball2 = gameScene->GetGameObject(4);
	static_cast<Transform*>(ball2->GetTransform())->SetPosition({900, 300, -2});
	ball2->AddComponent(new SpriteRenderer(ball2, gameScene->GetRenderer(), GetBallSprite(), ballSprRect, ballSprRect));
	ball2->AddComponent(new BoxCollider(ball2, {48, 48}));

	//gameScene->DEBUG_PrintGameObjAdd();

	//static_cast<Rigidbody*>(gb->GetComponent("Rigidbody"))->AddForce({10, 0, 0});
}
