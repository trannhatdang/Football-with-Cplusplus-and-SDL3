#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "engine/dg_engine_std.h"
#include "engine/components/component.h"

class Transform : public Component
{
	private:
		Vector3 m_ogPos;
		Vector3 m_pos;
		Vector3 m_rot;
	public:
		Transform(GameObject* gameObject, const Vector3& pos = {0, 0, 0}, const Vector3& rot = {0, 0, 0});
		void OnStart();
		void OnFixedIterate();
		void OnIterate();
		std::unique_ptr<Component> copy();
		Vector3 GetOGPosition() const;
		Vector3 GetPosition() const;
		void SetPosition(const Vector3& pos);
};

#endif
