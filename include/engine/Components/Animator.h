#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Component.h"
#include "../Animation.h"
#include "../AnimationNode.h"

class Animator : public Component
{
	private:
		SDL_Renderer* m_renderer;
		AnimationNode* m_currNode;
		std::unique_ptr<AnimationNode> m_anyNode;
		std::vector<std::unique_ptr<AnimationNode>> m_animations;
		void _addAllNextNodeOfThisNode(Animator* animator, AnimationNode* oldPrevNode, AnimationNode* newPrevNode, std::unordered_map<AnimationNode*, bool>* hasPrevMap);
	public:
		Animator(GameObject* obj, SDL_Renderer* renderer);
		AnimationNode* AddAnimation(AnimationNode* prevNode, SDL_Renderer* renderer, const std::string& filepath, int width, int height, int num_frame, int scale, cond_func* cond);
		AnimationNode* GetAnyNode();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
