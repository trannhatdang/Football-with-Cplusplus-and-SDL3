#include "engine/Components/BoxCollider.h"
#include "engine/GameObject.h"

static bool PointInBetweenPoints(int in, int l, int r)
{
	return in >= l && in <= r;
}

static bool CompareBox(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off)
{
	int box_min_x = pos.x;
	int box_max_x = pos.x + off.w;
	int box_min_y = pos.y;
	int box_max_y = pos.y + off.h;

	int other_box_min_x = other_pos.x;
	int other_box_max_x = other_pos.x + other_off.w;
	int other_box_min_y = other_pos.y;
	int other_box_max_y = other_pos.y + other_off.h;

	bool a = pos.x > other_pos.x + off.w; //left of it is to the right of other's right
	bool b = pos.x + off.w < other_pos.x; //right of it is to the left of other's left
	bool c = pos.y > other_pos.y + off.h; //top of it is under other
	bool d = pos.y + off.h < other_pos.y; //bottom of it is over other

	return !(a || b || c || d);
}

static int FindMinDist(int LDist, int RDist, int TDist, int BDist)
{
	LDist = std::abs(LDist);
	RDist = std::abs(RDist);
	TDist = std::abs(TDist);
	BDist = std::abs(BDist);

	if(LDist <= RDist && LDist <= TDist && LDist <= BDist)
	{
		return 0;
	}
	else if(RDist <= LDist && RDist <= TDist && RDist <= BDist)
	{
		return 1;
	}
	else if(TDist <= LDist && TDist <= RDist && TDist <= BDist)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

static PointDistInfo FindDistanceFromPointToEdgeOfBox(Vector3 pos, Vector3 other_pos, BColliderOff other_off)
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

	std::cout << "LDist: " << LDist << std::endl
		<< "RDist: " << RDist << std::endl
		<< "TDist: " << TDist << std::endl
		<< "BDist: " << BDist << std::endl;

	dists.push_back(LDist);
	dists.push_back(RDist);
	dists.push_back(TDist);
	dists.push_back(BDist);

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

	int other_box_min_x = other_pos.x;
	int other_box_max_x = other_pos.x + other_off.w;
	int other_box_min_y = other_pos.y;
	int other_box_max_y = other_pos.y + other_off.h;

	PointDistInfo vertex0_dist = FindDistanceFromPointToEdgeOfBox(vertex0, other_pos, other_off);
	PointDistInfo vertex1_dist = FindDistanceFromPointToEdgeOfBox(vertex1, other_pos, other_off);
	PointDistInfo vertex2_dist = FindDistanceFromPointToEdgeOfBox(vertex2, other_pos, other_off);
	PointDistInfo vertex3_dist = FindDistanceFromPointToEdgeOfBox(vertex3, other_pos, other_off);

	std::vector<PointDistInfo> ans;
	ans.reserve(4);

	if(vertex0_dist.isIn) ans.push_back(vertex0_dist);
	if(vertex1_dist.isIn) ans.push_back(vertex1_dist);
	if(vertex2_dist.isIn) ans.push_back(vertex2_dist);
	if(vertex3_dist.isIn) ans.push_back(vertex3_dist);

	int min_ind = 0;
	int size = ans.size();

	for(int i = 0; i < size - 1; ++i)
	{
		if(ans[i].dist.sqrMagnitude() < ans[i+1].dist.sqrMagnitude())
		{
			min_ind = i+1;
		}
	}

	return ans[min_ind];
}

void BoxCollider::MoveToFixedPosition(Vector3 pos, PointDistInfo info)
{
	if(!info.isIn) return;

	Transform* tfs = gameObject->GetTransform();
	pos += info.dist;
	tfs->SetPosition(pos);
}

BoxCollider::BoxCollider(GameObject* gameObject, const BColliderOff& offset, bool isTrigger) : Component("BoxCollider", gameObject), m_offset(offset), m_trigger(isTrigger) {}

void BoxCollider::OnStart()
{

}

void BoxCollider::OnIterate()
{
	SDL_Event box_event;
	box_event.type = BOX_POS_EVENT;

	Vector3 pos = static_cast<Transform*>(gameObject->GetTransform())->GetPosition();
	box_event.user.data1 = gameObject;

	if(SDL_PushEvent(&box_event) <= 0)
	{
		SDL_Log("Pushing event failed: %s", SDL_GetError());
	};
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
	if(event->type == BOX_POS_EVENT)
	{
		GameObject* other_obj = (GameObject*)(event->user.data1);
		if(other_obj == gameObject) return;

		BoxCollider* other_col = (BoxCollider*)other_obj->GetComponent("BoxCollider");

		if(other_col == NULL) // No collision
		{
			return;
		}

		Vector3 pos = static_cast<Transform*>(gameObject->GetTransform())->GetPosition();
		BColliderOff off = m_offset;
		Vector3 other_pos = ((Transform*)(other_obj->GetTransform()))->GetPosition();
		BColliderOff other_off = other_col->GetOffset();

		if(!CompareBox(pos, off, other_pos, other_off)) return; //No collision

		if(m_trigger)
		{
			gameObject->OnTriggerEnter(other_obj);
			other_obj->OnTriggerEnter(gameObject);
		}
		else
		{
			gameObject->OnCollisionEnter(other_obj);
			other_obj->OnCollisionEnter(gameObject);
			DoCollision(other_obj);
		}
	}

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
	Rigidbody* rb = (Rigidbody*)gameObject->GetComponent("Rigidbody");
	if(rb == NULL) return; //if gameobject does not have a rigidbody, it stays still
	
	Rigidbody* other_rb = (Rigidbody*)other_obj->GetComponent("Rigidbody");
	if(other_rb == NULL) //pushes itself away from stationary object
	{
		Vector3 pos = gameObject->GetTransform()->GetPosition();
		BColliderOff off = m_offset;
		Vector3 other_pos = other_obj->GetTransform()->GetPosition();
		BColliderOff other_off = static_cast<BoxCollider*>(other_obj->GetComponent("BoxCollider"))->GetOffset();

		auto dir_info = FindDirectionToPushAway(pos, off, other_pos, other_off);
		if(!dir_info.isIn) return;

		std::cout << dir_info.dist << std::endl;
		rb->MovePosition(pos + dir_info.dist);
	}

	auto momentum = rb->GetVelocity() * rb->GetMass();
	int other_momentum = 0;
}

std::unique_ptr<Component> BoxCollider::copy()
{
	return std::make_unique<BoxCollider>(gameObject, m_offset);
}

BColliderOff BoxCollider::GetOffset() const 
{
	return m_offset;
}

void BoxCollider::SetOffset(const BColliderOff& offset)
{
	m_offset = offset;
}
