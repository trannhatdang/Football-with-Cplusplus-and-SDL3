#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "engine/scene.h"
#include "engine/Components/SpriteRenderer.h"
#include "engine/Components/Rigidbody.h"
#include "engine/Components/Tilemap.h"
#include "engine/Components/Animator.h"
#include "engine/Components/BoxCollider.h"
#include "engine/Components/Font.h"
#include "Goal.h"
#include "AI.h"
#include "Controller.h"
#include "Movement.h"
#include "Config.h"

void GenerateGameScene(const std::unique_ptr<Scene>& gameScene);

#endif
