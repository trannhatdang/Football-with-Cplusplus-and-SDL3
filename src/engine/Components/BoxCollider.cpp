#include "engine/Components/BoxCollider.h"
#include "engine/GameObject.h"

BoxCollider::BoxCollider(GameObject* gameObject, const BColliderOff& offset) : Component("BoxCollider", gameObject), m_offset(offset) {}

void BoxCollider::OnStart()
{

}

void BoxCollider::OnIterate()
{
	SDL_Event box_event;
	box_event.type = BOX_MOVE_EVENT;

	Vector3 pos = static_cast<Transform*>(gameObject->GetTransform())->GetPosition();
	//std::cout << "in iterate: " << pos << std::endl;
	box_event.user.data1 = &(pos);

	SDL_PushEvent(&box_event);
}

void BoxCollider::OnEvent(SDL_Event* event)
{
	if(event->type == BOX_MOVE_EVENT)
	{
		auto pos = (Vector3*)event->user.data1;
		std::cout << *pos << std::endl;
	}
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
