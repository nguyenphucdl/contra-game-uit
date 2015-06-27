#include "MovementComponent.h"

#include "Framework\Utilities\Timer.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\GameObjects\Components\StaticComponent.h"
#include "Framework\Input\Input.h"
#include "Framework\Utilities\Console.h"
#include "Framework\Utilities\FPSCounter.h"

using namespace Framework;

MovementComponent::MovementComponent(Framework::GameObject* pOwner)
	: TransformComponent(pOwner)
	, m_currentState(SpriteStates::STATIONARY)
	, m_currentDirection(SpriteDirections::RIGHT)
	, m_floor(0.0f)
	, m_isJumping(false)
	, m_velocity(0.0f, 0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f, 0.0f)
	, m_isSupported(true)
	, m_gravitySupported(true)
	, m_movementSupported(true)
{
	memset(m_resolveOffset, 0, sizeof(m_resolveOffset));
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Initialize()
{
	//Framework::AttachComponentEvent(Events::COM_UPDATE_EVENT, GetOwner(), *this);
}

void MovementComponent::HandleEvent(Event* pEvent)
{
	switch (pEvent->GetID())
	{
	case Events::COM_UPDATE_EVENT:
	{
		PollInputUpdate();

		BehaviorUpdate();

		PostUpdate();
	}
		break;
	default:
		break;
	}
}

void MovementComponent::PostUpdate()
{
	//Update translation & apply gravity
	TransformComponent* pOwnerTransformComponent = component_cast<TransformComponent>(GetOwner());
	CollisionComponent* pOwnerCollisionComponent = component_cast<CollisionComponent>(GetOwner());

	if (pOwnerTransformComponent)
	{
		const Vector3& position = pOwnerTransformComponent->GetTransform()->GetTranslation();

		static const float ACCELERATION_MINIMUM = -20.0f;
		bool falling = m_acceleration.m_y < ACCELERATION_MINIMUM;//EPT_SILON

		Vector3 translation = m_velocity;
		translation.Multiply(Timer::GetSingleton().GetTimeSim());
		translation.Add(position);
		if (m_movementSupported)
			pOwnerTransformComponent->GetTransform()->SetTranslation(translation);


		float offset = pOwnerCollisionComponent->GetAABBMin().m_y - m_floor;
		if (offset > 5.0f)
		{
			m_onFloor = false;
		}
		else
		{
			m_isJumping = false;
			m_onFloor = true;
		}



		Timer& timer = Timer::GetSingleton();
		Vector3 accel = m_acceleration;
		accel.Multiply(timer.GetTimeSim());
		m_velocity.Add(accel);
		static const float GRAVITY_MULTIPLIER = 200.0f;
		static const float GRAVITY_CONSTANT = -9.8f;
		float dekta = GRAVITY_MULTIPLIER * GRAVITY_CONSTANT * timer.GetTimeSim();
		if (m_gravitySupported)
			m_acceleration.m_y += dekta;
		if (falling && m_isSupported)
		{
			m_acceleration.m_y = 0.0f;
			m_velocity.m_y = 0.0f;
		}
	}


	SetIsSupported(false, m_floor);

	//Update sprite states
	SpriteComponent* pSprite = component_cast<SpriteComponent>(GetOwner());
	pSprite->SetCurrentState(m_currentState);
	pSprite->SetCurrentDirection(m_currentDirection);
}

void MovementComponent::HandleCollision(CollisionEventData* pData)
{
	StaticComponent* pStaticComponent = component_cast<StaticComponent>(pData->m_pCollider);
	if (pStaticComponent)
	{
		if (pStaticComponent->GetStaticObjectType() == ObjectTypes::RANGE_OF_MOMENT)
		{
			return;
		}

		CollisionComponent* pTargetCollisionComponent = component_cast<CollisionComponent>(pData->m_pCollider);
		CollisionComponent* pObjectCollisionComponent = component_cast<CollisionComponent>(GetOwner());
		
		if (pTargetCollisionComponent && pObjectCollisionComponent)
		{
			//Scan
			ScanCollisionRun(pObjectCollisionComponent, pTargetCollisionComponent);


			//Logic
			if (m_collisionDirection == CollisionDirections::TOP)
			{
				float floor_y = pStaticComponent->GetRenderable().GetTransform().GetTranslation().m_y;
				SetIsSupported(true, floor_y);
			}

			//Resolve
			ResolveCollisionRun();
		}
	}
}

void MovementComponent::ScanCollisionRun(CollisionComponent* pObject, CollisionComponent* pTarget, float epsilon)
{
	Vector3 minAABBObject = pObject->GetAABBMin();
	Vector3 maxAABBObject = pObject->GetAABBMax();
	Vector3 minAABBCollider = pTarget->GetAABBMin();
	Vector3 maxAABBCollider = pTarget->GetAABBMax();

	m_offset[CollisionDirections::TOP] = pObject->GetAABBMin().m_y - pTarget->GetAABBMax().m_y;
	m_offset[CollisionDirections::RIGHT] = pObject->GetAABBMin().m_x - pTarget->GetAABBMax().m_x;
	m_offset[CollisionDirections::BOTTOM] = pTarget->GetAABBMin().m_y - pObject->GetAABBMax().m_y;
	m_offset[CollisionDirections::LEFT] = pTarget->GetAABBMin().m_x - pObject->GetAABBMax().m_x;

	if ((m_offset[CollisionDirections::TOP] > -epsilon && m_offset[CollisionDirections::RIGHT] > -epsilon)
		|| (m_offset[CollisionDirections::BOTTOM] > -epsilon && m_offset[CollisionDirections::LEFT] > -epsilon))
	{
		return;
	}

	int smallest = INT_MIN, idxSmallest = CollisionDirections::NONE;
	for (int i = 0; i < 4; i++) {
		if (m_offset[i] > smallest) {
			smallest = m_offset[i];
			idxSmallest = i;
		}
	}
	m_collisionDirection = (CollisionDirections)idxSmallest;
	m_resolveOffset[m_collisionDirection] = m_offset[m_collisionDirection];
}

void MovementComponent::ResolveCollisionRun()
{
	if (m_collisionDirection == CollisionDirections::TOP)
	{
		m_transform->GetTranslation().m_y -= m_resolveOffset[CollisionDirections::TOP];
	}
	else if (m_collisionDirection == CollisionDirections::LEFT)
	{
		m_transform->GetTranslation().m_x += m_resolveOffset[CollisionDirections::LEFT];
	}
	else if (m_collisionDirection == CollisionDirections::RIGHT)
	{
		m_transform->GetTranslation().m_x -= m_resolveOffset[CollisionDirections::RIGHT];
	}
	else if (m_collisionDirection == CollisionDirections::BOTTOM)
	{
		m_transform->GetTranslation().m_y += m_resolveOffset[CollisionDirections::BOTTOM];
		m_velocity.m_y = 0;
	}
}

