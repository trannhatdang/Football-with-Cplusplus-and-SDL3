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

	auto twall = gameScene->AddGameObject("TWall", "Wall");
	static_cast<Transform*>(twall->GetTransform())->SetPosition({0, 0, -2});
	twall->AddComponent(new Rigidbody(twall, true, 1, 100000));
	twall->AddComponent(new BoxCollider(twall, {1120, 10}));

	auto bwall = gameScene->AddGameObject("BWall", "Wall");
	static_cast<Transform*>(bwall->GetTransform())->SetPosition({0, 790, -2});
	bwall->AddComponent(new BoxCollider(bwall, {1120, 10}));

	auto lwall = gameScene->AddGameObject("LWall", "Wall");
	static_cast<Transform*>(lwall->GetTransform())->SetPosition({0, 0, -2});
	lwall->AddComponent(new BoxCollider(lwall, {10, 800}));

	auto rwall = gameScene->AddGameObject("RWall", "Wall");
	static_cast<Transform*>(rwall->GetTransform())->SetPosition({1110, 0, -2});
	rwall->AddComponent(new BoxCollider(rwall, {10, 800}));

	auto player1 = gameScene->AddGameObject("Player1", "Player");
	static_cast<Transform*>(player1->GetTransform())->SetPosition({100, 300, -2});
	player1->AddComponent(new SpriteRenderer(player1, gameScene->GetRenderer(), GetPlayerSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	player1->AddComponent(new Rigidbody(player1, true, 100, 60));
	player1->AddComponent(new BoxCollider(player1, {40, 40}));
	player1->AddComponent(new Movement(player1, 50.0f, true, true));

	auto player2 = gameScene->AddGameObject("Player2", "Player");
	static_cast<Transform*>(player2->GetTransform())->SetPosition({1000, 300, -2});
	player2->AddComponent(new SpriteRenderer(player2, gameScene->GetRenderer(), GetPlayerTwoSpriteSheet(), playerSprRect, {0, 0, 40, 40}));
	player2->AddComponent(new Rigidbody(player2, true, 5, 60));
	player2->AddComponent(new BoxCollider(player2, {40, 40}));
	player2->AddComponent(new Movement(player2, 5.0f, true, false));

	auto ball = gameScene->AddGameObject("Ball", "Ball");
	static_cast<Transform*>(ball->GetTransform())->SetPosition({560, 400, -2});
	ball->AddComponent(new SpriteRenderer(ball, gameScene->GetRenderer(), GetBallSprite(), ballSprRect, ballSprRect));
	ball->AddComponent(new Rigidbody(ball, true, 1));
	ball->AddComponent(new BoxCollider(ball, {48, 48}));

	auto ball2 = gameScene->AddGameObject("Ball2", "Ball");
	static_cast<Transform*>(ball2->GetTransform())->SetPosition({900, 300, -2});
	ball2->AddComponent(new SpriteRenderer(ball2, gameScene->GetRenderer(), GetBallSprite(), ballSprRect, ballSprRect));
	ball2->AddComponent(new BoxCollider(ball2, {48, 48}));

	//gameScene->DEBUG_PrintGameObjAdd();

	//static_cast<Rigidbody*>(gb->GetComponent("Rigidbody"))->AddForce({10, 0, 0});
}
