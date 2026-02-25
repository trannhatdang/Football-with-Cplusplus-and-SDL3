#include "engine/Components/Rigidbody.h"
#include "engine/GameObject.h"

void Rigidbody::_drag()
{
	if(m_velocity.sqrMagnitude() > 0)
	{
		auto val = 1 - 0.016 * m_drag;
		m_velocity *= val;
	}
}

Rigidbody::Rigidbody(GameObject* gameObject, bool hasDrag, int drag) : Component("Rigidbody", gameObject), m_hasDrag(hasDrag), m_drag(drag) {}

Rigidbody::~Rigidbody() {}

void Rigidbody::OnFixedIterate()
{
	Vector3 pos = gameObject->GetTransform()->GetPosition();

	m_acceleration = m_force_applied / m_mass;
	m_velocity += m_acceleration;
	pos += m_velocity;

	this->MovePosition(pos);
	if(m_hasDrag)
	{
		_drag();
	}

	m_acceleration = Vector3fZero();
	m_force_applied = Vector3fZero();
}

void Rigidbody::OnIterate()
{

}


int Rigidbody::GetMass() const
{
	return m_mass;
}

Vector3f Rigidbody::GetVelocity() const
{
	return m_velocity;
}

std::unique_ptr<Component> Rigidbody::copy()
{
	return std::make_unique<Rigidbody>(gameObject);
}

void Rigidbody::MovePosition(const Vector3& pos)
{
	gameObject->GetTransform()->SetPosition(pos);
}

void Rigidbody::AddForce(const Vector3f& force)
{
	m_force_applied += force;
}
