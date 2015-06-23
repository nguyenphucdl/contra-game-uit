#include "CollisionComponent.h"
#include "TransformComponent.h"
#include "../../EventManager/EventManager.h"
#include "../GameObject.h"

namespace Framework
{
	CollisionComponent::CollisionComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_isAttached(false)
		, m_AABBMin(-1.0f, -1.0f, 1.0f)
		, m_AABBMax(-1.0f, -1.0f, 1.0f)
		, m_lastAABBMin(-1.0f, -1.0f, 1.0f)
		, m_lastAABBMax(-1.0f, -1.0f, 1.0f)
		, m_active(false)
	{

	}

	CollisionComponent::~CollisionComponent()
	{
	}

	void CollisionComponent::Initialize()
	{
		Framework::AttachComponentEvent(Events::COM_COLLISION_EVENT, GetOwner(), *this);
		Framework::AttachComponentEvent(Events::COM_POST_UPDATE_EVENT, GetOwner(), *this);
	}

	bool CollisionComponent::Intersects(CollisionComponent& target)
	{
		bool intersecting = true;

		Vector3 thisMin = this->GetAABBMin();
		Vector3 thisMax = this->GetAABBMax();

		Vector3 targetMin = target.GetAABBMin();
		Vector3 targetMax = target.GetAABBMax();

		if (thisMin.m_x >= targetMax.m_x ||
			thisMax.m_x <= targetMin.m_x ||
			thisMin.m_y >= targetMax.m_y ||
			thisMax.m_y <= targetMin.m_y)
		{
			intersecting = false;
		}
		return intersecting;
	}

	bool CollisionComponent::SweptAABB(CollisionComponent& target)
	{
		Vector3 thisMove = this->m_AABBMin;
		thisMove.Subtract(this->m_lastAABBMin);

		D3DXVECTOR2 tEntry;//Thoi gian de o vi tri last cham target 
		D3DXVECTOR2 tExit;//Thoi gian de o vi tri last vuot qua target 
		D3DXVECTOR2 dEntry;//Khoang cach de last cham target
		D3DXVECTOR2 dExit;//Khoang cach de last vuot qua target
		float entryTime, exitTime;

		//Xet theo phuong X
		if (thisMove.m_x > 0)//Di chuyen qua phai
		{
			dEntry.x = target.GetAABBMin().m_x - this->m_lastAABBMax.m_x;
			dExit.x = target.GetAABBMax().m_x - this->m_lastAABBMin.m_x;
		}
		else if (thisMove.m_x < 0)//Di chuyen qua trai
		{
			dEntry.x = target.GetAABBMax().m_x - this->m_lastAABBMin.m_x;
			dExit.x = target.GetAABBMin().m_x - this->m_lastAABBMax.m_x;
		}

		if (thisMove.m_y > 0)//Di chuyen len tren
		{
			dEntry.y = target.GetAABBMin().m_y - this->m_lastAABBMax.m_y;
			dExit.y = target.GetAABBMax().m_y - this->m_lastAABBMin.m_y;
		}
		else if (thisMove.m_y < 0)//Di chuyen xuong duoi
		{
			dEntry.y = target.GetAABBMax().m_y - this->m_lastAABBMin.m_y;
			dEntry.y = target.GetAABBMin().m_y - this->m_lastAABBMax.m_y;
		}

		//find fraction of time when it occurs the collision

		if (thisMove.m_x == 0.0f)
		{
			tEntry.x = -std::numeric_limits<float>::infinity();
			tExit.x = std::numeric_limits<float>::infinity();
		}
		else
		{
			tEntry.x = dEntry.x / thisMove.m_x;
			tExit.x = dExit.x / thisMove.m_x;
		}

		if (thisMove.m_y == 0.0f)
		{
			tEntry.y = -std::numeric_limits<float>::infinity();
			tExit.y = std::numeric_limits<float>::infinity();
		}
		else
		{
			tEntry.y = dEntry.y / thisMove.m_y;
			tExit.y = dExit.y / thisMove.m_y;
		}

		entryTime = max(tEntry.x, tEntry.y);
		exitTime = min(tExit.x, tExit.y);

		//if there are no collision
		if (entryTime > exitTime || tEntry.x < 0.0f && tEntry.y < 0.0f || tEntry.x > 1.0f || tEntry.y > 1.0f)
		{
			//DIRECTION = none
			return false;
		}
		//there are collision
		else
		{ 
			if (tEntry.x >= tEntry.y)
			{
				if (thisMove.m_x > 0.0f)
				{
					//DIRECTION = RIGHT
				}
				else
				{
					//DIRECTION = LEFT
				}
			}
			else
			{
				if (thisMove.m_y > 0.0f)
				{
					//DIRECTTION = UP
				}
				else
				{
					//DIRECTION = DOWN
				}
			}
		}


		/*IMPORTANT*/
		m_AABBMin.Set(m_lastAABBMin);
		m_AABBMax.Set(m_lastAABBMax);
		return true;
	}

	void CollisionComponent::HandleEvent(Event* pEvent)
	{
		switch (pEvent->GetID())
		{
		case Events::COM_COLLISION_EVENT:
			{
				CollisionEventData* pCollisionData = static_cast<CollisionEventData*>(pEvent->GetData());
				if (pCollisionData && pCollisionData->m_pCollider)
				{
					for (CollisionListenerVectorIterator iter = m_eventListeners.begin(); iter != m_eventListeners.end(); ++iter)
					{
						(*iter)->HandleCollision(pCollisionData);
					}
				}
			}
			break;
		case Events::COM_POST_UPDATE_EVENT:
			{
				if (m_isAttached)
				{
					Vector3 boundMin = m_renderable->GetBoundMin();

					m_lastAABBMax.Set(m_AABBMax);
					m_lastAABBMin.Set(m_AABBMin);
					Transform::Vector3Transform(&boundMin, &boundMin, &m_renderable->GetTransform());
					m_AABBMax.Set(boundMin.m_x + m_renderable->GetBoundMax().m_x, boundMin.m_y, 1.0f);
					m_AABBMin.Set(boundMin.m_x, boundMin.m_y - m_renderable->GetBoundMax().m_y, 1.0f);
				}
				else
				{
					Log::error("Try get aabb max without attach renderable!");	
				}
			}
			break;
		default:
			break;
		}
	}
}

