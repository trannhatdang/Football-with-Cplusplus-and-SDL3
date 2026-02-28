#include "engine/Components/BoxCollider.h"
#include "engine/Components/Rigidbody.h"
#include "engine/GameObject.h"
#include "engine/Scene.h"

static bool PointInBetweenPoints(int in, int l, int r)
{
	return in >= l && in <= r;
}

static bool CompareBox(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off, bool can_equal = false, bool debug = false)
{

	if(debug)
	{
		std::cout << "comparing box: " << std::endl;
		std::cout << pos << off.w << ' ' << off.h << std::endl;
		std::cout << other_pos << other_off.w << ' ' << other_off.h << std::endl;
	}
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

static PointDistInfo FindDistanceFromPointToEdgeOfBox(Vector3 point_pos, Vector3 box_pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off, int offset = 10)
{
	int other_box_min_x = other_pos.x;
	int other_box_max_x = other_pos.x + other_off.w;
	int other_box_min_y = other_pos.y;
	int other_box_max_y = other_pos.y + other_off.h;

	std::cout << "finding if point is in other box: " << std::endl;
	std::cout << point_pos.x << ' ' << other_box_min_x << ' ' << other_box_max_x << std::endl;
	std::cout << point_pos.y << ' ' << other_box_min_y << ' ' << other_box_max_y << std::endl;
	if(!PointInBetweenPoints(point_pos.x, other_box_min_x, other_box_max_x) || !PointInBetweenPoints(point_pos.y, other_box_min_y, other_box_max_y))
	{
		return {false, {0, 0, 0}};
	}

	std::vector<int> dists;
	dists.reserve(4);

	int LDist = other_box_min_x - point_pos.x - offset;
	int RDist = other_box_max_x - point_pos.x + offset;
	int TDist = other_box_min_y - point_pos.y - offset;
	int BDist = other_box_max_y - point_pos.y + offset;

	dists.push_back(LDist);
	dists.push_back(RDist);
	dists.push_back(TDist);
	dists.push_back(BDist);

	Vector3 l_vec = {LDist, 0, 0};
	Vector3 r_vec = {RDist, 0, 0};
	Vector3 t_vec = {0, TDist, 0};
	Vector3 b_vec = {0, BDist, 0};

	std::vector<Vector3> vecs = {l_vec, r_vec, t_vec, b_vec};

	std::cout << l_vec << ' ' << r_vec << ' ' << t_vec << ' ' << b_vec << std::endl;

	//printf("LDist: %d; RDist: %d; TDist: %d; BDist: %d\n", LDist, RDist, TDist, BDist);

	int res = -1;

	for(int i = 0; i < 4; ++i)
	{
		if(!CompareBox(box_pos + vecs[i], off, other_pos, other_off, false, true))
		{
			res = i;
			break;
		}
	}

	if (res < 0)
	{
		return { false, {0, 0, 0} };
	}

	std::cout << "trying to find correct dir: " << std::endl;
	for(int i = 0; i < 4; ++i)
	{
		std::cout << std::abs(dists[i]) << ' ' << std::abs(dists[res]) << ' ';
		if((std::abs(dists[i]) < std::abs(dists[res])) && !CompareBox(box_pos + vecs[i], off, other_pos, other_off, false, true))
		{
			res = i;
		}
	}

	std::cout << std::endl << "correct dir: " << vecs[res] << std::endl;

	switch(res)
	{
		case 0:
			return {true, l_vec};
			break;
		case 1:
			return {true, r_vec};
			break;
		case 2:
			return {true, t_vec};
			break;
		case 3:
			return {true, b_vec};
			break;
		default:
			return {false, {0, 0, 0}};
			break;
	}
}

static Vector3 FindDisplacementVec(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off, Vector3 dir)
{
	const int MAX_ITERATE = 1000000;

	Vector3 ans = {0, 0, 0};

	for(int i = 0; i < MAX_ITERATE; ++i)
	{
		ans += dir;

		if(!CompareBox(pos, off, other_pos, other_off))
		{
			break;
		}
	}

	return ans;
}

static PointDistInfo FindDirectionToPushAway(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off, int offset = 0)
{
	/*Vector3 vertex0 = pos;
	Vector3 vertex1 = pos + Vector3(off.w, 0, 0);
	Vector3 vertex2 = pos + Vector3(off.w, off.h, 0);
	Vector3 vertex3 = pos + Vector3(0, off.h, 0);

	std::cout << "ver0: " << std::endl;
	PointDistInfo vertex0_dist = FindDistanceFromPointToEdgeOfBox(vertex0, pos, off, other_pos, other_off, offset);
	std::cout << "ver1: " << std::endl;
	PointDistInfo vertex1_dist = FindDistanceFromPointToEdgeOfBox(vertex1, pos, off, other_pos, other_off, offset);
	std::cout << "ver2: " << std::endl;
	PointDistInfo vertex2_dist = FindDistanceFromPointToEdgeOfBox(vertex2, pos, off, other_pos, other_off, offset);
	std::cout << "ver3: " << std::endl;
	PointDistInfo vertex3_dist = FindDistanceFromPointToEdgeOfBox(vertex3, pos, off, other_pos, other_off, offset);

	std::cout << "ver0: " << vertex0_dist.isIn << ' ' << vertex0_dist.dist << std::endl;
	std::cout << "ver1: " << vertex1_dist.isIn << ' ' << vertex1_dist.dist << std::endl;
	std::cout << "ver2: " << vertex2_dist.isIn << ' ' << vertex2_dist.dist << std::endl;
	std::cout << "ver3: " << vertex3_dist.isIn << ' ' << vertex3_dist.dist << std::endl;

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
		if(ans[min_ind].dist.sqrMagnitude() > ans[i].dist.sqrMagnitude())
		{
			min_ind = i;
		}
	}

	return ans[min_ind];*/

	Vector3 l_vec = FindDisplacementVec(pos, off, other_pos, other_off, {-1, 0, 0});
	Vector3 r_vec = FindDisplacementVec(pos, off, other_pos, other_off, {1, 0, 0});
	Vector3 t_vec = FindDisplacementVec(pos, off, other_pos, other_off, {0, -1, 0});
	Vector3 b_vec = FindDisplacementVec(pos, off, other_pos, other_off, {0, 1, 0});

	std::vector<Vector3> vecs = {l_vec, r_vec, t_vec, b_vec};

	int min_index = 0;
	for(int i = 1; i < 4; ++i)
	{
		if(vecs[min_index].sqrMagnitude() > vecs[i].sqrMagnitude())
		{
			min_index = i;
		}
	}

	return {true, vecs[min_index]};
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
		std::cout << gameObject->GetName() << std::endl;
		auto dir_info = FindDirectionToPushAway(pos, off, other_pos, other_off, 10);
		if(dir_info.isIn)
		{
			std::cout << "final dist: " << dir_info.dist << std::endl;
			rb->MovePosition(pos + dir_info.dist);

			return;
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
	
	//std::cout << gameObject->GetName() << " colliding with " << other_obj->GetName() << std::endl;
	//std::cout << gameObject->GetName() << vel << ' ' << vel_after << std::endl;
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
