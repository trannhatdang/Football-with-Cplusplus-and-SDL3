#include "engine/Components/BoxCollider.h"
#include "engine/Components/Rigidbody.h"
#include "engine/GameObject.h"
#include "engine/Scene.h"

static bool CompareBox(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off, bool can_equal = false, bool debug = false)
{
	bool a = false, b = false, c = false, d = false;
	if(can_equal)
	{
		a = pos.x >= other_pos.x + other_off.w; //left of it is to the right of other's right
		b = pos.x + off.w <= other_pos.x; //right of it is to the left of other's left
		c = pos.y >= other_pos.y + other_off.h; //top of it is under other
		d = pos.y + off.h <= other_pos.y; //bottom of it is over other
	}
	else
	{
		a = pos.x > other_pos.x + other_off.w; //left of it is to the right of other's right
		b = pos.x + off.w < other_pos.x; //right of it is to the left of other's left
		c = pos.y > other_pos.y + other_off.h; //top of it is under other
		d = pos.y + off.h < other_pos.y; //bottom of it is over other
	}


	return !(a || b || c || d);
}

BoxCollider::BoxCollider(GameObject* gameObject, const BColliderOff& offset, bool isTrigger) : Component("BoxCollider", gameObject), m_trigger(isTrigger), m_offset(offset) 
{
	gameObject->GetScene()->RegisterCollider(this);
}

Vector3 BoxCollider::findDisplacementVec(const Vector3& pos, const Vector3& dir) const
{
	const int MAX_ITERATE = 1000000;

	Vector3 ans = {0, 0, 0};

	for(int i = 0; i < MAX_ITERATE; ++i)
	{
		ans += dir;

		if(!checkCollision(ans + pos))
		{
			break;
		}
	}

	return ans;
}

Vector3 BoxCollider::findDirectionToPushAway(const Vector3& pos) const
{
	Vector3 l_vec = findDisplacementVec(pos, {-1, 0, 0});
	Vector3 tl_vec = findDisplacementVec(pos, {-1, -1, 0});
	Vector3 t_vec = findDisplacementVec(pos, {0, -1, 0});
	Vector3 tr_vec = findDisplacementVec(pos, {1, -1, 0});
	Vector3 r_vec = findDisplacementVec(pos, {1, 0, 0});
	Vector3 rb_vec = findDisplacementVec(pos, {1, 1, 0});
	Vector3 b_vec = findDisplacementVec(pos, {0, 1, 0});
	Vector3 bl_vec = findDisplacementVec(pos, {-1, 1, 0});

	std::vector<Vector3> vecs = {
		l_vec, tl_vec, t_vec, tr_vec,
		r_vec, rb_vec, b_vec, bl_vec
	};

	int min_index = 0;
	for(int i = 0; i < 8; ++i)
	{
		if(vecs[min_index].sqrMagnitude() > vecs[i].sqrMagnitude())
		{
			min_index = i;
		}
	}

	return vecs[min_index];
}

void BoxCollider::checkCollisionOfCurr()
{
	auto colls = gameObject->GetScene()->GetColliders();
	int size = colls.size();
	for(int i = 0; i < size; ++i)
	{
		auto other_col = colls[i];
		GameObject* other_obj = other_col->gameObject;
		if(other_col == this || m_objectsCollided.find(other_obj) != m_objectsCollided.end()) continue;

		Vector3 pos = static_cast<Transform*>(gameObject->GetTransform())->GetPosition();
		BColliderOff off = m_offset;
		Vector3 other_pos = ((Transform*)(other_obj->GetTransform()))->GetPosition();
		BColliderOff other_off = other_col->GetOffset();

		if(!CompareBox(pos, off, other_pos, other_off)) continue; //No collision

		Collide(other_obj);
	}
}

void BoxCollider::CheckCollision()
{
	checkCollisionOfCurr();
	m_objectsCollided.clear();
}

void BoxCollider::OnStart()
{

}

void BoxCollider::OnFixedIterate()
{

}

void BoxCollider::OnIterate()
{

}

void BoxCollider::OnDraw(SDL_Renderer* renderer)
{
	if(!m_debug) return;

	auto pos = gameObject->GetTransform()->GetPosition();

	SDL_FRect rect = {(float)pos.x, (float)pos.y, (float)m_offset.w, (float)m_offset.h};

	if(!SDL_RenderRect(renderer, &rect))
	{
		SDL_Log("Rendering Box Collider Debug Rect failed: %s", SDL_GetError());
	}
}

void BoxCollider::OnEvent(SDL_Event* event)
{
	if(event->type == SDL_EVENT_KEY_DOWN && event->key.down)
	{
		auto keyEvent = event->key;
		if(keyEvent.key == SDLK_F)
		{
			m_debug = !m_debug;
		}
	}
}

void BoxCollider::DoCollision(GameObject* other_obj)
{
	if(m_objectsCollided.find(other_obj) != m_objectsCollided.end()) return;
	if(other_obj == gameObject) return;

	Rigidbody* rb = (Rigidbody*)gameObject->GetComponent("Rigidbody");
	if(rb == NULL) return; //if gameobject does not have a rigidbody, it stays still
	
	m_objectsCollided.insert(other_obj);

	BoxCollider* other_col = (BoxCollider*)other_obj->GetComponent("BoxCollider");

	Rigidbody* other_rb = (Rigidbody*)other_obj->GetComponent("Rigidbody");
	Vector3 pos = gameObject->GetTransform()->GetPosition();

	auto dir_info = findDirectionToPushAway(pos);
	rb->MovePosition(pos + dir_info);

	if(other_rb == NULL) return;

	//calculatinng vel after: https://en.wikipedia.org/wiki/Elastic_collision
	int mass = rb->GetMass();
	int other_mass = other_rb->GetMass();
	Vector3f vel = rb->GetVelocity();
	Vector3f other_vel = other_rb->GetVelocity();

	//https://en.wikipedia.org/wiki/Elastic_collision
	Vector3 center = GetCenter();
	Vector3 other_center = other_col->GetCenter();

	float operand1 = (2.0f * other_mass) / (mass + other_mass);
	float operand2 = Vector3f_Dot(vel - other_vel, center - other_center) / (center - other_center).sqrMagnitude();
	float operand = operand1 * operand2;

	Vector3f cen_diff = center - other_center;
	Vector3f cen_operand = operand * cen_diff;

	Vector3f vel_after = vel - cen_operand;

	if(vel.magnitude() > 1000)
	{
		std::cout << gameObject->GetName() << " colliding with " << other_obj->GetName() << std::endl;
		std::cout << "mass: " << mass << " " << other_mass << std::endl;
		std::cout << "vel: " << vel << " " << other_vel << std::endl;

		std::cout << "operand1: " << operand1 << std::endl;
		std::cout << "vel diff: " << vel - other_vel << std::endl;
		std::cout << "center diff: " << center - other_center << std::endl;
		std::cout << "dot: " << Vector3f_Dot(vel - other_vel, center - other_center) << std::endl;

		std::cout << "center: " << center << std::endl;
		std::cout << "other_center: " << other_center << std::endl;
		std::cout << "center diff sqrmag: " << (center - other_center).sqrMagnitude() << std::endl;

		std::cout << "operand2: " << operand2 << std::endl;

		std::cout << "operand: " << operand << std::endl;
		std::cout << "cen_operand: " << cen_operand << std::endl;

		std::cout << gameObject->GetName() << vel << ' ' << vel_after << std::endl;
	}

	rb->SetVelocity(vel_after);

}

void BoxCollider::Collide(GameObject* other_obj)
{
	if(m_objectsCollided.find(other_obj) != m_objectsCollided.end()) return;

	if(m_trigger)
	{
		gameObject->OnTriggerEnter(other_obj);
	}
	else
	{
		gameObject->OnCollisionEnter(other_obj);
		DoCollision(other_obj);
		static_cast<BoxCollider*>(other_obj->GetComponent("BoxCollider"))->Collide(gameObject);
	}
}

BColliderOff BoxCollider::GetOffset() const 
{
	return m_offset;
}

Vector3 BoxCollider::GetCenter() const
{
	if(m_custom_center)
	{
		return m_center;
	}
	else
	{
		auto pos = gameObject->GetTransform()->GetPosition();

		return { pos.x + m_offset.w/2, pos.y + m_offset.h/2, pos.z };
	}
}

void BoxCollider::SetOffset(const BColliderOff& offset)
{
	m_offset = offset;
}

void BoxCollider::SetCenter(const Vector3& center)
{
	m_custom_center = true;
	m_center = center;
}

Vector3 BoxCollider::CheckPath(const Vector3& pos, const Vector3f& dir)
{
	Vector3 old_pos = pos;
	Vector3 new_pos = pos;
	Vector3 lim = old_pos + Vector3(std::round(dir.x), std::round(dir.y), std::round(dir.z));
	Vector3f new_dir = Vector3f_Zero();
	Vector3 new_dir_int = {0, 0, 0};
	Vector3f unit_vector = Vector3f_GetUnitVector(dir);
	bool limit = false;
	bool collided = false;
	int i = 0;

	//std::cout << "unit vector: " << unit_vector << std::endl;

	const int MAX_ITERATE = 100000000;

	for(i = 0; i < MAX_ITERATE; ++i)
	{
		new_dir = unit_vector * i;
		new_dir_int = Vector3(std::round(new_dir.x), std::round(new_dir.y), std::round(new_dir.z));

		old_pos = new_pos;
		new_pos = new_dir_int + pos;

		if(new_dir_int.magnitude() > dir.magnitude())
		{
			new_pos = lim;
			limit = true;
		}

		if(CheckCollision(new_pos))
		{
			collided = true;
		}

		if(limit || collided)
		{
			break;
		}
	}
	
	if(gameObject->GetName() == "Ball")
	{
		//std::cout << "check path iterated: " << i << std::endl;
		//std::cout << "pos: " << pos << std::endl;
		//std::cout << "unit: " << unit_vector << std::endl;
		//std::cout << "dir: " << dir << std::endl;
		//std::cout << "new_dir_int: " << new_dir_int << std::endl;
		//std::cout << "old_pos: " << old_pos << std::endl;
		//std::cout << "new_pos: " << new_pos << std::endl;
		//std::cout << "collided: " << (collided ? "true" : "false") << std::endl;
		//std::cout << "limit: " << (limit ? "true" : "false") << std::endl;
		//std::cout << "lim: " << lim << std::endl;

	}


	if(i == MAX_ITERATE - 1)
	{
		std::cout << "CheckPath happened too many times, check BoxCollider" << std::endl;
		return lim;
	}

	return new_pos;
}

bool BoxCollider::CheckCollision(const Vector3& pos) const
{
	auto colls = gameObject->GetScene()->GetColliders();
	int size = colls.size();
	for(int i = 0; i < size; ++i)
	{
		auto other_col = colls[i];
		if(other_col == this || other_col->m_trigger) continue;

		GameObject* other_obj = other_col->gameObject;

		BColliderOff off = m_offset;
		Vector3 other_pos = ((Transform*)(other_obj->GetTransform()))->GetPosition();
		BColliderOff other_off = other_col->GetOffset();

		if(CompareBox(pos, off, other_pos, other_off))
		{
			return true;
		}
	}

	return false;
}


std::unique_ptr<Component> BoxCollider::copy()
{
	return std::make_unique<BoxCollider>(gameObject, m_offset);
}
