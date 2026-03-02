#include "CustomScene/GameScene/Wind.h"
#include "engine/GameObject.h"


Wind::Wind(GameObject* obj) : Component("Wind", obj)
{

}

void Wind::OnIterate()
{

}

void Wind::OnFixedIterate()
{
	if(rand() % 10 == 0){
		auto rb = (Rigidbody*)gameObject->GetComponent("Rigidbody");
		rb->AddVelocity(0.1f*m_speed);

	}
}

std::unique_ptr<Component> Wind::copy()
{
	return std::make_unique<Wind>(gameObject);
}

Vector3f Wind::GetWindSpeed() const
{
	return m_speed;
}

void Wind::SetWindSpeed(const Vector3f& spd)
{
	m_speed = spd;
}

void Wind::Reset()
{
	m_speed = {0, 0, 0};
}
