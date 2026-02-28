#include "engine/Components/Rigidbody.h"
#include "engine/GameObject.h"

void Rigidbody::_drag()
{
	if(m_velocity.sqrMagnitude() > 0)
	{
		auto dragForceMagnitude = m_velocity.sqrMagnitude() * m_drag;
		auto dragForceVector = dragForceMagnitude * -1.0f * Vector3f_GetUnitVector(m_velocity) * 0.01f;

		//std::cout << dragForceVector << std::endl;
		this->AddForce(dragForceVector);

		//auto val = 1 - 0.016 * m_drag;
		//m_velocity *= val;
	}
}

Rigidbody::Rigidbody(GameObject* gameObject, bool hasDrag, int drag, int mass) : Component("Rigidbody", gameObject), m_mass(mass), m_drag(drag), m_hasDrag(hasDrag)
{

}

Rigidbody::~Rigidbody() {}

void Rigidbody::OnFixedIterate()
{
	Vector3 pos = gameObject->GetTransform()->GetPosition();

	m_acceleration = m_force_applied / m_mass;
	m_velocity = Vector3f_Clamp(m_velocity + m_acceleration, m_min_vel, m_max_vel);

	if(std::round(m_velocity.magnitude()) == 0) return;

	BoxCollider* coll = (BoxCollider*)gameObject->GetComponent("BoxCollider");
	if(coll && m_velocity.magnitude() < 10e3) //just, let it through if it wants to go that bad
	{
		pos = coll->CheckPath(pos, m_velocity);
	}
	else
	{
		pos += m_velocity;
	}

	this->MovePosition(pos);
	m_acceleration = Vector3f_Zero();
	m_force_applied = Vector3f_Zero();
	if(m_hasDrag)
	{
		_drag();
	}
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

void Rigidbody::SetVelocity(const Vector3f& vec)
{
	m_velocity = Vector3f_Clamp(vec, m_min_vel, m_max_vel);
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
