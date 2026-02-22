#include "engine/Components/Animator.h"

Animator::Animator(GameObject* obj) : Component("Animator", obj)
{

}

AnimationNode* Animator::AddAnimation(AnimationNode* prevNode, SDL_Renderer* renderer, const std::string& filepath, int width, int height, int num_frame, int scale, cond_func* cond)
{
	//either its 2AM or this code is super weird
	auto node = new AnimationNode;
	node->anim = std::make_unique<Animation>(renderer, filepath, width, height, num_frame, scale);

	prevNode->adj.push_back(node);
	prevNode->conds.push_back(cond);
	m_animations.emplace_back(node);

	return node;
}
