#include "engine/Components/BoxCollider.h"

BoxCollider::BoxCollider(GameObject* gameObject, const BColliderOff& offset) : Component("BoxCollider", gameObject), m_offset(offset) {}

void BoxCollider::OnStart()
{

}

void BoxCollider::OnIterate()
{

}

void BoxCollider::OnEvent(SDL_Event* event)
{

}

std::unique_ptr<Component> BoxCollider::copy()
{
	return std::make_unique<BoxCollider>(gameObject, m_offset);
}

const BColliderOff& BoxCollider::GetOffset() const 
{
	return m_offset;
}

void BoxCollider::SetOffset(const BColliderOff& offset)
{
	m_offset = offset;
}
