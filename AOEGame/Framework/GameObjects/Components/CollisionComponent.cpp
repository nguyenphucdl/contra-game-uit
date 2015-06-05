#include "CollisionComponent.h"
#include "TransformComponent.h"
#include "../../EventManager/EventManager.h"
#include "../GameObject.h"

namespace Framework
{
	CollisionComponent::CollisionComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_isAttached(false)
	{

	}

	CollisionComponent::~CollisionComponent()
	{
	}

	void CollisionComponent::Initialize()
	{
		//Framework::AttachEvent(Events::SCE_COLLISION_EVENT, *this);
		Framework::AttachEventComponent(Events::COM_COLLISION_EVENT, this->GetOwner(), *this);
	}

	const Vector3 CollisionComponent::GetAABBMin()
	{
		Vector3 boundMin, aabbMin;
		if (this->m_isAttached)
		{
			boundMin = m_renderable->GetBoundMin();
			Transform::Vector3Transform(&boundMin, &boundMin, &m_renderable->GetTransform());
			aabbMin.Set(boundMin.m_x, boundMin.m_y - m_renderable->GetBoundMax().m_y, 1.0f);
		}
		else
		{
			Log::error("Try get aabb min without attach renderable!");
		}
		return aabbMin;
	}

	const Vector3 CollisionComponent::GetAABBMax()
	{
		Vector3 boundMin, aabbMax;
		if (this->m_isAttached)
		{
			boundMin = m_renderable->GetBoundMin();
			Transform::Vector3Transform(&boundMin, &boundMin, &m_renderable->GetTransform());
			aabbMax.Set(boundMin.m_x + m_renderable->GetBoundMax().m_x, boundMin.m_y, 1.0f);
		}
		else
		{
			Log::error("Try get aabb max without attach renderable!");
		}
		return aabbMax;
	}

	bool CollisionComponent::Intersects(CollisionComponent& target)
	{
		bool intersecting = true;

		Vector3 thisMin = this->GetAABBMin();
		Vector3 thisMax = this->GetAABBMax();

		/*TransformComponent* pThisTransformComponent = component_cast<TransformComponent>(GetOwner());
		if (pThisTransformComponent)
		{
			Transform* transform = pThisTransformComponent->GetTransform();
			thisMin.Add(transform->GetTranslation());
			thisMax.Add(transform->GetTranslation());
		}*/

		Vector3 targetMin = target.GetAABBMin();
		Vector3 targetMax = target.GetAABBMax();

		/*TransformComponent* pTargetTransformComponent = component_cast<TransformComponent>(target.GetOwner());
		if (pTargetTransformComponent)
		{
			Transform* transform = pTargetTransformComponent->GetTransform();
			targetMin.Add(transform->GetTranslation());
			targetMax.Add(transform->GetTranslation());
		}*/

		if (thisMin.m_x >= targetMax.m_x ||
			thisMax.m_x <= targetMin.m_x ||
			thisMin.m_y >= targetMax.m_y ||
			thisMax.m_y <= targetMin.m_y)
		{
			intersecting = false;
		}
		return intersecting;
	}

	void CollisionComponent::HandleEvent(Event* pEvent)
	{
		if (pEvent->GetID() == Events::COM_COLLISION_EVENT)
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
	}
}

