#include "engine/Components/Animator.h"

Animator::Animator(GameObject* obj, SDL_Renderer* renderer) : Component("Animator", obj), m_renderer(renderer)
{

}

AnimationNode* Animator::AddAnimation(AnimationNode* prevNode, SDL_Renderer* renderer, const std::string& filepath, int width, int height, int num_frame, int scale, cond_func* cond)
{
	//im too stupid
	AnimationNode* node = new AnimationNode;
	node->anim = std::make_unique<Animation>(renderer, filepath, width, height, num_frame, scale);

	if(prevNode)
	{
		prevNode->adj.push_back(node);
		prevNode->conds.push_back(cond);
	}

	m_animations.emplace_back(node);

	return node;
}

AnimationNode* Animator::GetAnyNode()
{
	return m_anyNode.get();
}

void Animator::OnIterate()
{
	for(auto i = 0; i < m_anyNode->conds.size(); ++i)
	{
		if(m_anyNode->conds[i](this->gameObject))
		{
			m_currNode = m_anyNode->adj[i];
			return;
		}
	}

	for(auto i = 0; i < m_currNode->conds.size(); ++i)
	{
		if(m_currNode->conds[i](this->gameObject))
		{
			m_currNode = m_currNode->adj[i];
			return;
		}
	}
}

//I WILL NEVER COPY

std::unique_ptr<Component> Animator::copy()
{
	Animator* new_comp = new Animator(gameObject, m_renderer);
	std::unordered_map<AnimationNode*, bool> hasPrevMap;

	_addAllNextNodeOfThisNode(new_comp, m_anyNode.get(), &hasPrevMap);

	for(auto i = 0; i < m_animations.size(); ++i)
	{
		AnimationNode* ptr = m_animations[i].get();
		_addAllNextNodeOfThisNode(new_comp, ptr, &hasPrevMap);
	}
	
	new_comp->AddAnimation(nullptr, m_renderer, m_anyNode->anim->GetFilepath(), m_anyNode->anim->GetWidth(),
				m_anyNode->anim->GetHeight(), m_anyNode->anim->GetNumFrames(), m_anyNode->anim->GetScale(), nullptr);
	for(auto i = 0; i < m_animations.size(); ++i)
	{
		AnimationNode* ptr = m_animations[i].get();
		if(hasPrevMap.count(ptr) == 0) //doesnt have previous
		{
			new_comp->AddAnimation(nullptr, m_renderer, ptr->anim->GetFilepath(), ptr->anim->GetWidth(),
				ptr->anim->GetHeight(), ptr->anim->GetNumFrames(), ptr->anim->GetScale(), nullptr);
		}
	}

	return std::unique_ptr<Animator>(new_comp);
}

void Animator::_addAllNextNodeOfThisNode(Animator* animator, AnimationNode* prevNode, std::unordered_map<AnimationNode*, bool>* hasPrevMap)
{
	for(auto i = 0; i < prevNode->adj.size(); ++i)
	{
		auto nextNode = prevNode->adj[i];
		animator->AddAnimation(prevNode, m_renderer, nextNode->anim->GetFilepath(), nextNode->anim->GetWidth(), 
				nextNode->anim->GetHeight(), nextNode->anim->GetNumFrames(), nextNode->anim->GetScale(), 
				prevNode->conds[i]);
		
		hasPrevMap->insert({nextNode, true});
	}
}
