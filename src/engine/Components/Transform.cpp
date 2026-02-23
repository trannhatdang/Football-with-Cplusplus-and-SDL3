#include "engine/Components/Transform.h"

Transform::Transform(GameObject* gameObject, const Vector3& pos, const Vector3& rot) : Component("Transform", gameObject), m_pos(pos), m_rot(rot)
{

}

void Transform::OnFixedIterate()
{
}

void Transform::OnIterate()
{

}

std::unique_ptr<Component> Transform::copy()
{
	return std::make_unique<Transform>(gameObject, m_pos, m_rot);
}

Vector3 Transform::GetPosition() const
{
	return m_pos;
}

void Transform::SetPosition(const Vector3& pos)
{
	m_pos = pos;
}
