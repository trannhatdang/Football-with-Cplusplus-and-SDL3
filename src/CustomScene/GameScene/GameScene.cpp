#include "CustomScene/GameScene/GameScene.h"

static SDL_FRect playerSrcRect = {0, 0, 80, 80};
static SDL_FRect playerDstRect = {0, 0, 40, 40};
static SDL_FRect ballSrcRect = {0, 0, 48, 48};

static bool CheckFacingLeft(GameObject* obj)
{
	Rigidbody* rb = (Rigidbody*)obj->GetComponent("Rigidbody");
	Vector3f vel = rb->GetVelocity();

	return Vector3f_GetPrimaryDirection(vel) == Vector3f_Left();
}

static bool CheckFacingUp(GameObject* obj)
{
	Rigidbody* rb = (Rigidbody*)obj->GetComponent("Rigidbody");
	Vector3f vel = rb->GetVelocity();

	return Vector3f_GetPrimaryDirection(vel) == Vector3f_Up();
}

static bool CheckFacingRight(GameObject* obj)
{
	Rigidbody* rb = (Rigidbody*)obj->GetComponent("Rigidbody");
	Vector3f vel = rb->GetVelocity();

	return Vector3f_GetPrimaryDirection(vel) == Vector3f_Right();
}

static bool CheckFacingDown(GameObject* obj)
{
	Rigidbody* rb = (Rigidbody*)obj->GetComponent("Rigidbody");
	Vector3f vel = rb->GetVelocity();

	return Vector3f_GetPrimaryDirection(vel) == Vector3f_Down();
}

void GenerateGameScene(const std::unique_ptr<Scene>& gameScene)
{
	//tilemap
	gameScene->AddGameObject("Tilemap", "Tilemap");
	auto tilemap_gb = gameScene->GetGameObject(0);

	std::vector<std::vector<int>> map = 
		{{6, 2, 2, 2, 2, 2, 7},
		{10, 0, 0, 0, 0, 0, 11},
		{4, 0, 0, 1, 0, 0, 5},
		{10, 0, 0, 0, 0, 0, 11},
		{9, 3, 3, 3, 3, 3, 8}};

	tilemap_gb->AddComponent(new Tilemap(tilemap_gb, gameScene->GetRenderer(), GetGrassSpriteSheet(), map, 160, 160));

	//walls
	auto twall = gameScene->AddGameObject("TWall", "Wall");
	static_cast<Transform*>(twall->GetTransform())->SetPosition({0, -100, -2});
	twall->AddComponent(new Rigidbody(twall, true, 1, 100000));
	twall->AddComponent(new BoxCollider(twall, {1120, 110}));

	auto bwall = gameScene->AddGameObject("BWall", "Wall");
	static_cast<Transform*>(bwall->GetTransform())->SetPosition({0, 790, -2});
	bwall->AddComponent(new BoxCollider(bwall, {1120, 110}));

	auto lwall = gameScene->AddGameObject("LWall", "Wall");
	static_cast<Transform*>(lwall->GetTransform())->SetPosition({-100, 10, -2});
	lwall->AddComponent(new BoxCollider(lwall, {110, 780}));

	auto rwall = gameScene->AddGameObject("RWall", "Wall");
	static_cast<Transform*>(rwall->GetTransform())->SetPosition({1110, 10, -2});
	rwall->AddComponent(new BoxCollider(rwall, {110, 780}));

	//players
	auto striker1 = gameScene->AddGameObject("Striker1", "Player");
	static_cast<Transform*>(striker1->GetTransform())->SetPosition({500 - 20, 400 - 20, -2});

	auto striker1_anim = (Animator*)striker1->AddComponent(new Animator(striker1, gameScene->GetRenderer()));
	auto player_one_right_striker1_anim_node = striker1_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(0), playerSrcRect, playerDstRect, 1, 1, &CheckFacingRight);
	striker1_anim->SetStartNode(player_one_right_striker1_anim_node);

	striker1_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(1), playerSrcRect, playerDstRect, 1, 1, &CheckFacingDown);
	striker1_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(2), playerSrcRect, playerDstRect, 1, 1, &CheckFacingLeft);
	striker1_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(3), playerSrcRect, playerDstRect, 1, 1, &CheckFacingUp);

	striker1->AddComponent(new Rigidbody(striker1, true, 100, 60));
	striker1->AddComponent(new BoxCollider(striker1, {40, 40}));
	striker1->AddComponent(new Movement(striker1, 50.0f, true, true));

	auto midfielder10 = gameScene->AddGameObject("Midfielder10", "Player");
	static_cast<Transform*>(midfielder10->GetTransform())->SetPosition({350 - 20, 400 - 150 - 20, -2});

	auto midfielder10_anim = (Animator*)midfielder10->AddComponent(new Animator(midfielder10, gameScene->GetRenderer()));
	auto player_one_right_midfielder10_anim_node = midfielder10_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(0), playerSrcRect, playerDstRect, 1, 1, &CheckFacingRight);
	midfielder10_anim->SetStartNode(player_one_right_midfielder10_anim_node);

	midfielder10_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(1), playerSrcRect, playerDstRect, 1, 1, &CheckFacingDown);
	midfielder10_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(2), playerSrcRect, playerDstRect, 1, 1, &CheckFacingLeft);
	midfielder10_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(3), playerSrcRect, playerDstRect, 1, 1, &CheckFacingUp);

	midfielder10->AddComponent(new Rigidbody(midfielder10, true, 100, 60));
	midfielder10->AddComponent(new BoxCollider(midfielder10, {40, 40}));
	midfielder10->AddComponent(new Movement(midfielder10, 50.0f, false, true));

	auto midfielder11 = gameScene->AddGameObject("Midfielder11", "Player");
	static_cast<Transform*>(midfielder11->GetTransform())->SetPosition({350 - 20, 400 + 150 - 20, -2});

	auto midfielder11_anim = (Animator*)midfielder11->AddComponent(new Animator(midfielder11, gameScene->GetRenderer()));
	auto player_one_right_midfielder11_anim_node = midfielder11_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(0), playerSrcRect, playerDstRect, 1, 1, &CheckFacingRight);
	midfielder11_anim->SetStartNode(player_one_right_midfielder11_anim_node);

	midfielder11_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(1), playerSrcRect, playerDstRect, 1, 1, &CheckFacingDown);
	midfielder11_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(2), playerSrcRect, playerDstRect, 1, 1, &CheckFacingLeft);
	midfielder11_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(3), playerSrcRect, playerDstRect, 1, 1, &CheckFacingUp);

	midfielder11->AddComponent(new Rigidbody(midfielder11, true, 100, 60));
	midfielder11->AddComponent(new BoxCollider(midfielder11, {40, 40}));
	midfielder11->AddComponent(new Movement(midfielder11, 50.0f, false, true));

	auto defender1 = gameScene->AddGameObject("Defender1", "Player");
	static_cast<Transform*>(defender1->GetTransform())->SetPosition({200 - 20, 400 - 20, -2});
	
	auto defender1_anim = (Animator*)defender1->AddComponent(new Animator(defender1, gameScene->GetRenderer()));
	auto player_one_right_defender1_anim_node = defender1_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(0), playerSrcRect, playerDstRect, 1, 1, &CheckFacingRight);
	defender1_anim->SetStartNode(player_one_right_defender1_anim_node);

	defender1_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(1), playerSrcRect, playerDstRect, 1, 1, &CheckFacingDown);
	defender1_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(2), playerSrcRect, playerDstRect, 1, 1, &CheckFacingLeft);
	defender1_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(3), playerSrcRect, playerDstRect, 1, 1, &CheckFacingUp);

	defender1->AddComponent(new Rigidbody(defender1, true, 100, 60));
	defender1->AddComponent(new BoxCollider(defender1, {40, 40}));
	defender1->AddComponent(new Movement(defender1, 50.0f, false, true));

	auto goalkeeper1 = gameScene->AddGameObject("Goalkeeper1", "Player");
	static_cast<Transform*>(goalkeeper1->GetTransform())->SetPosition({100 - 20, 400 - 20, -2});

	auto goalkeeper1_anim = (Animator*)goalkeeper1->AddComponent(new Animator(goalkeeper1, gameScene->GetRenderer()));
	auto player_one_right_goalkeeper1_anim_node = goalkeeper1_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(0), playerSrcRect, playerDstRect, 1, 1, &CheckFacingRight);
	goalkeeper1_anim->SetStartNode(player_one_right_goalkeeper1_anim_node);

	goalkeeper1_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(1), playerSrcRect, playerDstRect, 1, 1, &CheckFacingDown);
	goalkeeper1_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(2), playerSrcRect, playerDstRect, 1, 1, &CheckFacingLeft);
	goalkeeper1_anim->AddAnimation(nullptr, GetPlayerTopdownSprite(3), playerSrcRect, playerDstRect, 1, 1, &CheckFacingUp);

	goalkeeper1->AddComponent(new Rigidbody(goalkeeper1, true, 100, 60));
	goalkeeper1->AddComponent(new BoxCollider(goalkeeper1, {40, 40}));
	goalkeeper1->AddComponent(new Movement(goalkeeper1, 50.0f, false, true));

	auto striker2 = gameScene->AddGameObject("Striker2", "Player");
	static_cast<Transform*>(striker2->GetTransform())->SetPosition({620 - 20, 400 - 20, -2});

	auto striker2_anim = (Animator*)striker2->AddComponent(new Animator(striker2, gameScene->GetRenderer()));

	striker2_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(0), playerSrcRect, playerDstRect, 1, 1, &CheckFacingRight);
	striker2_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(1), playerSrcRect, playerDstRect, 1, 1, &CheckFacingDown);

	auto player_two_left_striker2_anim_node = striker2_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(2), playerSrcRect, playerDstRect, 1, 1, &CheckFacingLeft);
	striker2_anim->SetStartNode(player_two_left_striker2_anim_node);

	striker2_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(3), playerSrcRect, playerDstRect, 1, 1, &CheckFacingUp);
	
	striker2->AddComponent(new Rigidbody(striker2, true, 100, 60));
	striker2->AddComponent(new BoxCollider(striker2, {40, 40}));
	striker2->AddComponent(new Movement(striker2, 50.0f, true, false));

	auto midfielder20 = gameScene->AddGameObject("Midfielder20", "Player");
	static_cast<Transform*>(midfielder20->GetTransform())->SetPosition({770 - 20, 400 - 150 - 20, -2});

	auto midfielder20_anim = (Animator*)midfielder20->AddComponent(new Animator(midfielder20, gameScene->GetRenderer()));

	midfielder20_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(0), playerSrcRect, playerDstRect, 1, 1, &CheckFacingRight);
	midfielder20_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(1), playerSrcRect, playerDstRect, 1, 1, &CheckFacingDown);

	auto player_two_left_midfielder20_anim_node = midfielder20_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(2), playerSrcRect, playerDstRect, 1, 1, &CheckFacingLeft);
	midfielder20_anim->SetStartNode(player_two_left_midfielder20_anim_node);

	midfielder20_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(3), playerSrcRect, playerDstRect, 1, 1, &CheckFacingUp);

	midfielder20->AddComponent(new Rigidbody(midfielder20, true, 100, 60));
	midfielder20->AddComponent(new BoxCollider(midfielder20, {40, 40}));
	midfielder20->AddComponent(new Movement(midfielder20, 50.0f, false, false));

	auto midfielder21 = gameScene->AddGameObject("Midfielder21", "Player");
	static_cast<Transform*>(midfielder21->GetTransform())->SetPosition({770 - 20, 400 + 150 - 20, -2});

	auto midfielder21_anim = (Animator*)midfielder21->AddComponent(new Animator(midfielder21, gameScene->GetRenderer()));

	midfielder21_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(0), playerSrcRect, playerDstRect, 1, 1, &CheckFacingRight);
	midfielder21_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(1), playerSrcRect, playerDstRect, 1, 1, &CheckFacingDown);

	auto player_two_left_midfielder21_anim_node = midfielder21_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(2), playerSrcRect, playerDstRect, 1, 1, &CheckFacingLeft);
	midfielder21_anim->SetStartNode(player_two_left_midfielder21_anim_node);

	midfielder21_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(3), playerSrcRect, playerDstRect, 1, 1, &CheckFacingUp);

	midfielder21->AddComponent(new Rigidbody(midfielder21, true, 100, 60));
	midfielder21->AddComponent(new BoxCollider(midfielder21, {40, 40}));
	midfielder21->AddComponent(new Movement(midfielder21, 50.0f, false, false));

	auto defender2 = gameScene->AddGameObject("Defender2", "Player");
	static_cast<Transform*>(defender2->GetTransform())->SetPosition({920 - 20, 400 - 20, -2});

	auto defender2_anim = (Animator*)defender2->AddComponent(new Animator(defender2, gameScene->GetRenderer()));

	defender2_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(0), playerSrcRect, playerDstRect, 1, 1, &CheckFacingRight);
	defender2_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(1), playerSrcRect, playerDstRect, 1, 1, &CheckFacingDown);

	auto player_two_left_defender2_anim_node = defender2_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(2), playerSrcRect, playerDstRect, 1, 1, &CheckFacingLeft);
	defender2_anim->SetStartNode(player_two_left_defender2_anim_node);

	defender2_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(3), playerSrcRect, playerDstRect, 1, 1, &CheckFacingUp);

	defender2->AddComponent(new Rigidbody(defender2, true, 100, 60));
	defender2->AddComponent(new BoxCollider(defender2, {40, 40}));
	defender2->AddComponent(new Movement(defender2, 50.0f, false, false));

	auto goalkeeper2 = gameScene->AddGameObject("Goalkeeper2", "Player");
	static_cast<Transform*>(goalkeeper2->GetTransform())->SetPosition({1020 - 20, 400 - 20, -2});

	auto goalkeeper2_anim = (Animator*)goalkeeper2->AddComponent(new Animator(goalkeeper2, gameScene->GetRenderer()));

	goalkeeper2_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(0), playerSrcRect, playerDstRect, 1, 1, &CheckFacingRight);
	goalkeeper2_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(1), playerSrcRect, playerDstRect, 1, 1, &CheckFacingDown);

	auto player_two_left_goalkeeper2_anim_node = goalkeeper2_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(2), playerSrcRect, playerDstRect, 1, 1, &CheckFacingLeft);
	goalkeeper2_anim->SetStartNode(player_two_left_goalkeeper2_anim_node);

	goalkeeper2_anim->AddAnimation(nullptr, GetPlayerTwoTopdownSprite(3), playerSrcRect, playerDstRect, 1, 1, &CheckFacingUp);

	goalkeeper2->AddComponent(new Rigidbody(goalkeeper2, true, 100, 60));
	goalkeeper2->AddComponent(new BoxCollider(goalkeeper2, {40, 40}));
	goalkeeper2->AddComponent(new Movement(goalkeeper2, 50.0f, false, false));

	auto ball = gameScene->AddGameObject("Ball", "Ball");
	static_cast<Transform*>(ball->GetTransform())->SetPosition({560 - 24, 400 - 24, -2});
	ball->AddComponent(new SpriteRenderer(ball, gameScene->GetRenderer(), GetBallSprite(), ballSrcRect, ballSrcRect));
	ball->AddComponent(new Rigidbody(ball, true, 1));
	ball->AddComponent(new BoxCollider(ball, {48, 48}));

	//gameScene->DEBUG_PrintGameObjAdd();

	//static_cast<Rigidbody*>(gb->GetComponent("Rigidbody"))->AddForce({10, 0, 0});
}
