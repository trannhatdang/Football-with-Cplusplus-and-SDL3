#ifndef B_COLLIDER_H_
#define B_COLLIDER_H_

#include "engine/Components/Component.h"
#include <algorithm>
#include <unordered_set>

class Rigidbody;

//Only 2D and only box, normally this should inherit another collider component but this should do

typedef struct BColliderOff
{
	int w;
	int h;
} BColliderOff;

typedef struct PointDistInfo
{
	bool isIn;
	Vector3 dist;
} PointDistInfo;

class BoxCollider : public Component
{
	private:
		bool m_trigger = false;
		bool m_debug = false;
		BColliderOff m_offset;
		std::unordered_set<GameObject*> m_objectsCollided;

		Vector3 findDisplacementVec(const Vector3& pos, const Vector3& dir) const;
		Vector3 findDirectionToPushAway(const Vector3& pos) const;
		bool checkCollision(const Vector3& pos) const;
		void checkCollisionOfCurr();
	public:
		BoxCollider(GameObject* gameObject, const BColliderOff& offset, bool isTrigger = false);
		void CheckCollision();
		void OnStart();
		void OnIterate();
		void OnFixedIterate();
		void OnDraw(SDL_Renderer* renderer);
		void OnEvent(SDL_Event* event);
		void DoCollision(GameObject* other_obj);
		void Collide(GameObject* other_obj);
		BColliderOff GetOffset() const;
		void SetOffset(const BColliderOff& offset);
		Vector3 CheckPath(const Vector3& pos, const Vector3f& dir);

		std::unique_ptr<Component> copy();
};

#endif
