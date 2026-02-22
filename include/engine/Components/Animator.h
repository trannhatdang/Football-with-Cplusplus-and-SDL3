#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Component.h"
#include "../Animation.h"
#include "../AnimationNode.h"

class Animator : public Component
{
	private:
		AnimationNode* m_currNode;
		std::vector<std::unique_ptr<AnimationNode>> m_animations;

	public:
		Animator(GameObject* obj);
		AnimationNode* AddAnimation(AnimationNode* prevNode, SDL_Renderer* renderer, const std::string& filepath, int width, int height, int num_frame, int scale, cond_func* cond);
};

#endif
