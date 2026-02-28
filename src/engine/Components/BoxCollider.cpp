#include "engine/Components/BoxCollider.h"
#include "engine/Components/Rigidbody.h"
#include "engine/GameObject.h"
#include "engine/Scene.h"

static bool PointInBetweenPoints(int in, int l, int r)
{
	return in >= l && in <= r;
}

static bool CompareBox(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off, bool can_equal = false)
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

static PointDistInfo FindDistanceFromPointToEdgeOfBox(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off)
{
	int other_box_min_x = other_pos.x;
	int other_box_max_x = other_pos.x + other_off.w;
	int other_box_min_y = other_pos.y;
	int other_box_max_y = other_pos.y + other_off.h;

	if(!PointInBetweenPoints(pos.x, other_box_min_x, other_box_max_x) || !PointInBetweenPoints(pos.y, other_box_min_y, other_box_max_y))
	{
		return {false, {0, 0, 0}};
	}

	std::vector<int> dists;
	dists.reserve(4);

	int LDist = other_box_min_x - pos.x;
	int RDist = other_box_max_x - pos.x;
	int TDist = other_box_min_y - pos.y;
	int BDist = other_box_max_y - pos.y;

	dists.push_back(LDist);
	dists.push_back(RDist);
	dists.push_back(TDist);
	dists.push_back(BDist);

	//printf("LDist: %d; RDist: %d; TDist: %d; BDist: %d\n", LDist, RDist, TDist, BDist);

	int res = 0;

	for(int i = 1; i < 4; ++i)
	{
		if(std::abs(dists[res]) > std::abs(dists[i]))
		{
			res = i;
		}
	}

	switch(res)
	{
		case 0:
			return {true, {LDist, 0, 0}};
			break;
		case 1:
			return {true, {RDist, 0, 0}};
			break;
		case 2:
			return {true, {0, TDist, 0}};
			break;
		default:
			return {true, {0, BDist, 0}};
			break;
	}
}

static PointDistInfo FindDirectionToPushAway(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off)
{
	Vector3 vertex0 = pos;
	Vector3 vertex1 = pos + Vector3(off.w, 0, 0);
	Vector3 vertex2 = pos + Vector3(off.w, off.h, 0);
	Vector3 vertex3 = pos + Vector3(0, off.h, 0);

	PointDistInfo vertex0_dist = FindDistanceFromPointToEdgeOfBox(vertex0, off, other_pos, other_off);
	PointDistInfo vertex1_dist = FindDistanceFromPointToEdgeOfBox(vertex1, off, other_pos, other_off);
	PointDistInfo vertex2_dist = FindDistanceFromPointToEdgeOfBox(vertex2, off, other_pos, other_off);
	PointDistInfo vertex3_dist = FindDistanceFromPointToEdgeOfBox(vertex3, off, other_pos, other_off);

	std::vector<PointDistInfo> ans;
	ans.reserve(4);

	if(vertex0_dist.isIn) ans.push_back(vertex0_dist);
	if(vertex1_dist.isIn) ans.push_back(vertex1_dist);
	if(vertex2_dist.isIn) ans.push_back(vertex2_dist);
	if(vertex3_dist.isIn) ans.push_back(vertex3_dist);

	int min_ind = 0;
	int size = ans.size();

	if(size == 0)
	{
		return {false, {0, 0, 0}};
	}

	for(int i = 0; i < size - 1; ++i)
	{
		if(ans[min_ind].dist.sqrMagnitude() < ans[i].dist.sqrMagnitude())
		{
			min_ind = i;
		}
	}

	return ans[min_ind];
}

void BoxCollider::moveToFixedPosition(Vector3 pos, PointDistInfo info)
{
	if(!info.isIn) return;

	Transform* tfs = gameObject->GetTransform();
	pos += info.dist;
	tfs->SetPosition(pos);
}

bool BoxCollider::checkCollision(const Vector3& pos) const
{
	auto colls = gameObject->GetScene()->GetColliders();
	int size = colls.size();
	for(int i = 0; i < size; ++i)
	{
		auto other_col = colls[i];
		if(other_col == this) continue;

		GameObject* other_obj = other_col->gameObject;

		BColliderOff off = m_offset;
		Vector3 other_pos = ((Transform*)(other_obj->GetTransform()))->GetPosition();
		BColliderOff other_off = other_col->GetOffset();

		if(!CompareBox(pos, off, other_pos, other_off)) continue; //No collision

		return true;
	}

	return false;
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

BoxCollider::BoxCollider(GameObject* gameObject, const BColliderOff& offset, bool isTrigger) : Component("BoxCollider", gameObject), m_trigger(isTrigger), m_offset(offset) 
{
	gameObject->GetScene()->RegisterCollider(this);
}

void BoxCollider::OnStart()
{

}

void BoxCollider::OnFixedIterate()
{
	if (!gameObject->GetComponent("Rigidbody")) return;
	checkCollisionOfCurr();
	m_objectsCollided.clear();
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

	Rigidbody* other_rb = (Rigidbody*)other_obj->GetComponent("Rigidbody");
	Vector3 pos = gameObject->GetTransform()->GetPosition();
	BColliderOff off = m_offset;
	Vector3 other_pos = other_obj->GetTransform()->GetPosition();
	BColliderOff other_off = static_cast<BoxCollider*>(other_obj->GetComponent("BoxCollider"))->GetOffset();

	if(CompareBox(pos, off, other_pos, other_off, true))
	{
		auto dir_info = FindDirectionToPushAway(pos, off, other_pos, other_off);
		if(dir_info.isIn)
		{
			rb->MovePosition(pos + dir_info.dist);
		}
	}

	if(other_rb == NULL)  return; //pushes itself away from stationary object

	int mass = rb->GetMass();
	int other_mass = other_rb->GetMass();
	Vector3f vel = rb->GetVelocity();
	Vector3f other_vel = other_rb->GetVelocity();

	//https://en.wikipedia.org/wiki/Elastic_collision
	Vector3f vel_after = (mass - other_mass * 1.0f)/(mass + other_mass * 1.0f) * vel + (2.0f * other_mass)/(mass + other_mass * 1.0f) * other_vel;
	//Vector3f other_vel_after = (2 * mass)/(mass + other_mass) * vel + (other_mass - mass)/(mass + other_mass) * other_vel;
	
	std::cout << gameObject->GetName() << " colliding with " << other_obj->GetName() << std::endl;
	std::cout << gameObject->GetName() << vel << ' ' << vel_after << std::endl;
	rb->SetVelocity(vel_after * 0.9f);
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

void BoxCollider::SetOffset(const BColliderOff& offset)
{
	m_offset = offset;
}

Vector3 BoxCollider::CheckPath(const Vector3& pos, const Vector3f& dir) const
{
	Vector3 old_pos = pos;
	Vector3 new_pos = pos;
	Vector3 lim = old_pos + dir;
	Vector3f new_dir = Vector3f_Zero();
	Vector3 new_dir_int = {0, 0, 0};
	Vector3f unit_vector = Vector3f_GetUnitVector(dir);
	bool limit = false;
	bool collided = false;
	int i = 0;

	//std::cout << "unit vector: " << unit_vector << std::endl;

	const int MAX_ITERATE = 100000000;

	for(i = 1; i < MAX_ITERATE; ++i)
	{
		new_dir = unit_vector * i;
		new_dir_int = Vector3(std::round(new_dir.x), std::round(new_dir.y), std::round(new_dir.z));
			/*Vector3(new_dir.x > 0 ? (int)std::ceil(new_dir.x) : (int)std::floor(new_dir.x), 
				new_dir.y > 0 ? (int)std::ceil(new_dir.y) : (int)std::floor(new_dir.y), 
				new_dir.z > 0 ? (int)std::ceil(new_dir.z) : (int)std::floor(new_dir.z));*/

		old_pos = new_pos;
		new_pos = new_dir_int + pos;

		if((new_dir_int.x > 0 && new_pos.x > lim.x) || (new_dir_int.x < 0 && new_pos.x < lim.x)
			|| (new_dir_int.y > 0 && new_pos.y > lim.y) || (new_dir_int.y < 0 && new_pos.y < lim.y))
		{
			new_pos = lim;
			limit = true;
		}

		if(checkCollision(new_pos))
		{
			collided = true;
		}

		if(limit || collided)
		{
			break;
		}
	}

	/*
	std::cout << "check path iterated: " << i << std::endl;
	std::cout << "unit: " << unit_vector << std::endl;
	std::cout << "new_dir_int: " << new_dir_int << std::endl;
	std::cout << "old_pos: " << old_pos << std::endl;
	std::cout << "limit: " << (limit ? "true" : "false") << std::endl;
	std::cout << "lim: " << lim << std::endl;*/

	if(i == MAX_ITERATE - 1)
	{
		std::cout << "CheckPath happened too many times, check BoxCollider" << std::endl;
		return lim;
	}

	if(collided)
	{
		return new_pos;
	}
	else
	{
		return lim;
	}
}

std::unique_ptr<Component> BoxCollider::copy()
{
	return std::make_unique<BoxCollider>(gameObject, m_offset);
}
