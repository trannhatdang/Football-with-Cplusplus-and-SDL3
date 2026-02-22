#ifndef ANIMATION_NODE_H_
#define ANIMATION_NODE_H_

#include "dg_engine_std.h"
#include "engine/GameObject.h"
#include "Animation.h"

typedef bool cond_func(GameObject* obj);

typedef struct AnimationNode
{
	std::vector<AnimationNode*> adj;
	std::vector<cond_func*> conds;
	std::unique_ptr<Animation> anim;

} AnimationNode;

#endif
