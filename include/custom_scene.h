#ifndef CUSTOM_SCENE_H_
#define CUSTOM_SCENE_H_

#include "engine/scene.h"
#include "engine/Components/SpriteRenderer.h"
#include "engine/Components/Rigidbody.h"
#include "engine/Components/Tilemap.h"
#include "Config.h"

void GenerateGameScene(const std::unique_ptr<Scene>& gameScene);

#endif
