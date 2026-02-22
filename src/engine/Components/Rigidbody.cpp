#include "engine/Components/Rigidbody.h"
#include "engine/GameObject.h"

Rigidbody::Rigidbody(GameObject* gameObject, bool hasDrag, int drag) : Component("Rigidbody", gameObject), m_hasDrag(hasDrag), m_drag(drag) {}

Rigidbody::~Rigidbody() {}

void Rigidbody::OnFixedIterate()
{
	auto pos = gameObject->GetTransform()->GetPosition();

	m_acceleration = m_force_applied / m_mass;

	pos += m_velocity;
	m_velocity += m_acceleration;

	//std::cout << "vel: " << m_velocity << std::endl;

	this->MovePosition(pos);
	if(m_hasDrag)
	{
		_drag();
	}

	m_acceleration = GetVector3fZero();
	m_force_applied = GetVector3fZero();
}

void Rigidbody::OnIterate()
{

}

void Rigidbody::MovePosition(const Vector3& pos)
{
	gameObject->GetTransform()->SetPosition(pos);
}

void Rigidbody::AddForce(const Vector3f& force)
{
	m_force_applied += force;
}

void Rigidbody::_drag()
{
	if(m_velocity.sqrMagnitude() > 0)
	{
		auto val = 1 - 0.016 * m_drag;
		m_velocity *= val;
	}
}

std::unique_ptr<Component> Rigidbody::copy()
{
	return std::make_unique<Rigidbody>(gameObject);
}
