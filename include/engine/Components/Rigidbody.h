#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "engine/Components/Component.h"
#include "BoxCollider.h"
#include <cmath>
#include <algorithm>

class Rigidbody : public Component
{
	private:
		Vector3f m_acceleration = {0, 0, 0};
		Vector3f m_velocity = {0, 0, 0};
		Vector3f m_force_applied = {0, 0, 0};
		Vector3f m_max_vel = {1000, 1000, 1000};
		Vector3f m_min_vel = {-1000, -1000, -1000};
		Vector3 m_last_pos = {0, 0, 0};
		int m_mass = 1;
		int m_drag = 1;
		bool m_hasDrag = false;

		void _drag();
	public:
		Rigidbody(GameObject* gameObject, bool hasDrag = true, int drag = 1, int mass = 1);
		~Rigidbody();
		void OnFixedIterate();
		void OnIterate();
		std::unique_ptr<Component> copy();
		int GetMass() const;
		Vector3f GetVelocity() const;
		void SetVelocity(const Vector3f& vec);
		void AddVelocity(const Vector3f& vec);
		void MovePosition(const Vector3& pos, const Vector3& dir);
		void MovePosition(const Vector3& pos);
		void Reset();
		void AddForce(const Vector3f& force);
};

#endif
