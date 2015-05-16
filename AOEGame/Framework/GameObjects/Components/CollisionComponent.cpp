#include "CollisionComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"

namespace Framework
{
	CollisionComponent::CollisionComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_isAttached(false)
		, m_min(0.0f, 0.0f, 0.0f)
		, m_max(0.0f, 0.0f, 0.0f)
	{

	}

	CollisionComponent::~CollisionComponent()
	{
	}

	void CollisionComponent::Initialize()
	{

	}

	const Vector3& CollisionComponent::GetMin()
	{
		if (this->m_isAttached)
		{
			return m_renderable->GetBoundMin();
		}
		return m_min;
	}

	const Vector3& CollisionComponent::GetMax()
	{
		if (this->m_isAttached)
		{
			return m_renderable->GetBoundMax();
		}
		return m_max;
	}

	bool CollisionComponent::Intersects(CollisionComponent& target)
	{
		bool intersecting = true;

		Vector3 thisMin = this->GetMin();
		Vector3 thisMax = this->GetMax();

		/*TransformComponent* pThisTransformComponent = component_cast<TransformComponent>(GetOwner());
		if (pThisTransformComponent)
		{
			Transform* transform = pThisTransformComponent->GetTransform();
			thisMin.Add(transform->GetTranslation());
			thisMax.Add(transform->GetTranslation());
		}*/

		Vector3 targetMin = target.GetMin();
		Vector3 targetMax = target.GetMax();

		/*TransformComponent* pTargetTransformComponent = component_cast<TransformComponent>(target.GetOwner());
		if (pTargetTransformComponent)
		{
			Transform* transform = pTargetTransformComponent->GetTransform();
			targetMin.Add(transform->GetTranslation());
			targetMax.Add(transform->GetTranslation());
		}*/

		if (thisMin.m_x > targetMax.m_x ||
			thisMax.m_x < targetMin.m_x ||
			thisMin.m_y > targetMax.m_y ||
			thisMax.m_y < targetMin.m_y ||
			thisMin.m_z > targetMax.m_z ||
			thisMax.m_z < targetMin.m_z)
		{
			intersecting = false;
		}
		return intersecting;
	}

	void CollisionComponent::HandleEvent(Event* pEvent)
	{
		if (pEvent->GetID() == Events::COLLISION_EVENT)
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

