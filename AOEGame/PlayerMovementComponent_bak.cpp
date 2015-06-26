#include "PlayerMovementComponent.h"
#include "Framework\Utilities\Timer.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\GameObjects\Components\StaticComponent.h"
#include "Framework\Input\Input.h"
#include "Framework\Utilities\Console.h"
#include "Framework\Utilities\FPSCounter.h"
using namespace Framework;


PlayerMovementComponent::PlayerMovementComponent(GameObject* pOwner)
	: TransformComponent(pOwner)
	, m_currentState(SpriteStates::STATIONARY)
	, m_currentDirection(SpriteDirections::RIGHT)
	, m_floor(0.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f, 0.0f)
	, m_isSupported(true)
	, m_isClimping(false)
	, m_isJumping(false)
	, m_isKeyPress(false)
{
	memset(m_resolveOffset, 0, sizeof(m_resolveOffset));
}

PlayerMovementComponent::~PlayerMovementComponent()
{
}

void PlayerMovementComponent::Initialize()
{
	Framework::AttachComponentEvent(Events::COM_UPDATE_EVENT, GetOwner(), *this);
}

void PlayerMovementComponent::HandleEvent(Event* pEvent)
{
	switch (pEvent->GetID())
	{
	case Events::COM_UPDATE_EVENT:
	{
		_ProcessPollInput();

		PostUpdate();
	}
		break;
	default:
		break;
	}
}

void PlayerMovementComponent::_ProcessPollInput()
{
	m_isKeyPress = false;
	bool isMoveLeftRight = false;
	
	//TEST
	/*if (IS_KEYDOWN(DIK_UP))
	{
		m_velocity.m_y = 100.0f;
	}
	else if (IS_KEYDOWN(DIK_DOWN))
	{
		m_velocity.m_y = -100.0f;
	}
	else
	{
		m_velocity.m_y = 0.0f;
	}*/



	// PART1: Change states based on key input
	if (m_isClimping)
	{
		m_currentState = SpriteStates::CLIMB;
	}
	else
	{
		if (m_isJumping)
			m_currentState = SpriteStates::JUMP;
	}

	if (IS_KEYDOWN(DIK_LEFT))
	{
		isMoveLeftRight = true;
		m_isKeyPress = true;
		m_currentDirection = SpriteDirections::LEFT;
		if (!m_isClimping)
		{
			if (m_onFloor)
				m_currentState = SpriteStates::STATIONARY;
			if (!m_isJumping)
			{
				m_currentState = SpriteStates::MOVE;
				float moveVel = 150.0f;
				m_velocity.m_x = (m_currentDirection == SpriteDirections::LEFT) ? (-moveVel) : (moveVel);
			}
		}
	}
	else if (IS_KEYDOWN(DIK_RIGHT))
	{
		m_isKeyPress = true;
		isMoveLeftRight = true;
		m_currentDirection = SpriteDirections::RIGHT;
		if (!m_isClimping)
		{
			if (m_onFloor)
				m_currentState = SpriteStates::STATIONARY;
			if (!m_isJumping)
			{
				m_currentState = SpriteStates::MOVE;
				float moveVel = 150.0f;
				m_velocity.m_x = (m_currentDirection == SpriteDirections::LEFT) ? (-moveVel) : (moveVel);
			}
		}
	} 

	if (!m_isKeyPress)
	{
		if (!m_isClimping && m_onFloor && !m_isJumping)
			m_currentState = SpriteStates::STATIONARY;
		if (!m_isJumping)
			m_velocity.m_x = 0.0f;
	}

	if (IS_KEYDOWN(DIK_SPACE))
	{
		m_isKeyPress = true;
		if (m_onFloor)
		{
  			m_isJumping = true;
			m_currentState = SpriteStates::JUMP;

			static const float JUMP_ACCELERATION = 180.0f;
			m_acceleration.m_y = JUMP_ACCELERATION;
			m_velocity.m_y = 220.0f;
		}

	}

	if (IS_KEYDOWN(DIK_F))
	{
		m_isKeyPress = true;
		if (m_currentState == SpriteStates::MOVE)
			m_currentState = SpriteStates::MOVE_FIRING;
		else if (m_currentState == SpriteStates::STATIONARY)
			m_currentState = SpriteStates::STATIONARY_FIRING;
		else if (m_currentState == SpriteStates::JUMP)
			m_currentState = SpriteStates::JUMP_FIRING;
	}



	// PART2: Update value based on states

	if (m_currentState == SpriteStates::MOVE)
	{
		
	}
	else if (m_currentState == SpriteStates::JUMP)
	{
  		
	}
	else if (m_currentState == SpriteStates::CLIMBING || m_currentState == SpriteStates::CLIMB)
	{
		if (IS_KEYDOWN(DIK_UP))
		{
			m_velocity.m_y = 100.0f;
			//m_currentDirection = (m_currentDirection == SpriteDirections::LEFT) ? SpriteDirections::RIGHT : SpriteDirections::LEFT;
			m_currentState = SpriteStates::CLIMBING;
		}
		else if (IS_KEYDOWN(DIK_DOWN))
		{
			if (!m_onFloor)
				m_velocity.m_y = -100.0f;
			//m_currentDirection = (m_currentDirection == SpriteDirections::LEFT) ? SpriteDirections::RIGHT : SpriteDirections::LEFT;
			m_currentState = SpriteStates::CLIMBING;
		}
		else
		{
			m_currentState = SpriteStates::CLIMB;
			m_velocity.m_y = 0.0f;
		}
		if (isMoveLeftRight)
		{
			float moveInStairVel = 150.0f;
			m_velocity.m_x = (m_currentDirection == SpriteDirections::LEFT) ? (-moveInStairVel) : (moveInStairVel);
		}
		else
		{
			m_velocity.m_x = 0.0f;
		}
	}
	else if (m_currentState == SpriteStates::STATIONARY)
	{
		m_velocity.m_x = 0.0f;
		//m_velocity.m_y = 0.0f;
	}

		
	

}

void PlayerMovementComponent::PostUpdate()
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
		m_acceleration.m_y += dekta;
		if (falling && m_isSupported)
		{
			m_acceleration.m_y = 0.0f;
			m_velocity.m_y = 0.0f;
		}

		
		Console::GetSingletonPtr()->print("Player position (%f,%f)", position.m_x, position.m_y);
		Console::GetSingletonPtr()->print("Offset Resolve left(%f) right(%f) top(%f) bottom(%f)", m_resolveOffset[CollisionDirections::LEFT], m_resolveOffset[CollisionDirections::RIGHT], m_resolveOffset[CollisionDirections::TOP], m_resolveOffset[CollisionDirections::BOTTOM]);
		Console::GetSingletonPtr()->print("Offset left(%f) right(%f) top(%f) bottom(%f)", m_offset[CollisionDirections::LEFT], m_offset[CollisionDirections::RIGHT], m_offset[CollisionDirections::TOP], m_offset[CollisionDirections::BOTTOM]);
	}


	SetIsSupported(false, m_floor);
	m_isClimping = false;

	//Update sprite states
	SpriteComponent* pSprite = component_cast<SpriteComponent>(GetOwner());
	pSprite->SetCurrentState(m_currentState);
	pSprite->SetCurrentDirection(m_currentDirection);
}

void PlayerMovementComponent::HandleCollision(CollisionEventData* pData)
{
	StaticComponent* pStaticComponent = component_cast<StaticComponent>(pData->m_pCollider);
	if (pStaticComponent)
	{
		CollisionComponent* pTargetCollisionComponent = component_cast<CollisionComponent>(pData->m_pCollider);
		CollisionComponent* pObjectCollisionComponent = component_cast<CollisionComponent>(GetOwner());

		if (pTargetCollisionComponent && pObjectCollisionComponent)
		{
			//Scan
			ScanCollisionRun(pObjectCollisionComponent, pTargetCollisionComponent);

			//Logic
			if (pStaticComponent->GetStaticObjectType() == ObjectTypes::STAIRWAY_OBJECT)
			{
				if (abs(m_offset[m_collisionDirection]) > 30.0f)
					m_isClimping = true;
				return;
			}
			else if (pStaticComponent->GetStaticObjectType() == ObjectTypes::END_SCENE)
			{
				Framework::SendEvent(Events::SCE_COMPLETE_SCENE_EVENT);
			}
			else if (pStaticComponent->GetStaticObjectType() == ObjectTypes::RANGE_OF_MOMENT)
			{
				return;
			}
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

void PlayerMovementComponent::ScanCollisionRun(CollisionComponent* pObject, CollisionComponent* pTarget, float epsilon)
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

void PlayerMovementComponent::ResolveCollisionRun()
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







//void PlayerMovementComponent::HandleEvent222(Event* pEvent)
//{
//	switch (pEvent->GetID())
//	{
//	case Events::COM_UPDATE_EVENT:
//	{
//		_ProcessPollInput();
//
//
//
//		TransformComponent* pOwnerTransformComponent = component_cast<TransformComponent>(GetOwner());
//		CollisionComponent* pOwnerCollisionComponent = component_cast<CollisionComponent>(GetOwner());
//
//		if (pOwnerTransformComponent)
//		{
//			const Vector3& position = pOwnerTransformComponent->GetTransform()->GetTranslation();
//
//			static const float ACCELERATION_MINIMUM = -20.0f;
//			bool falling = m_acceleration.m_y < ACCELERATION_MINIMUM;//EPT_SILON
//
//			Vector3 translation = m_velocity;
//			translation.Multiply(Timer::GetSingleton().GetTimeSim());
//			translation.Add(position);
//
//			float offset = pOwnerCollisionComponent->GetAABBMin().m_y - m_floor;
//			if (offset > 5.0f)
//			{
//				m_onFloor = false;
//			}
//			else
//			{
//				m_isJumping = false;
//				m_onFloor = true;
//			}
//
//			/*Console::GetSingletonPtr()->print("Offset floor (%f)", offset);
//			if (m_isSupported && falling && m_vectorOffset.m_y > -25.0f)
//			{
//			translation.m_y -= m_vectorOffset.m_y;
//			m_onFloor = true;
//			}
//			else
//			{
//			m_onFloor = false;
//			}*/
//
//			pOwnerTransformComponent->GetTransform()->SetTranslation(translation);
//
//			Timer& timer = Timer::GetSingleton();
//			Vector3 accel = m_acceleration;
//			accel.Multiply(timer.GetTimeSim());
//			m_velocity.Add(accel);
//			static const float GRAVITY_MULTIPLIER = 200.0f;
//			static const float GRAVITY_CONSTANT = -9.8f;
//			float dekta = GRAVITY_MULTIPLIER * GRAVITY_CONSTANT * timer.GetTimeSim();
//			m_acceleration.m_y += dekta;
//			if (falling && m_isSupported)
//			{
//				m_acceleration.m_y = 0.0f;
//				m_velocity.m_y = 0.0f;
//			}
//
//			//Console::GetSingletonPtr()->print("Offset Vector m_x(%f) m_y(%f) m_z(%f)", m_vectorOffset.m_x, m_vectorOffset.m_y, m_vectorOffset.m_z);
//			//Console::GetSingletonPtr()->print("Offset left(%f) right(%f) top(%f) bottom(%f)", m_offset[3], m_offset[1], m_offset[0], m_offset[2]);
//			//Console::GetSingletonPtr()->print("Falling falling (%d) && On Floor(%d)", falling, m_onFloor);
//
//			//Console::GetSingletonPtr()->print("Player bound min m_y (%f)", pOwnerCollisionComponent->GetAABBMin().m_y);
//			Console::GetSingletonPtr()->print("Player position (%f,%f)", position.m_x, position.m_y);
//			//Console::GetSingletonPtr()->print("Is Climbing (%d)", m_isClimping);
//			//Console::GetSingletonPtr()->print("Is Supported (%d)", m_isSupported);
//			//Console::GetSingletonPtr()->print("Floor (%f)", m_floor);
//			//Console::GetSingletonPtr()->print("Is Jumping (%d)", m_isJumping);
//			//Console::GetSingletonPtr()->print("On Floor (%d)", m_onFloor);
//			//Console::GetSingletonPtr()->print("Anim (%f)", Timer::GetSingletonPtr()->GetAnim());
//			//Console::GetSingletonPtr()->print("Timer total %f", Timer::GetSingletonPtr()->GetTimeTotal());
//			//Console::GetSingletonPtr()->print("Offset left(%f) right(%f) top(%f) bottom(%f)", m_offset[3], m_offset[1], m_offset[0], m_offset[2]);
//			//Console::GetSingletonPtr()->print("Accel m_x(%f) m_y(%f)", m_acceleration.m_x ,m_acceleration.m_y);
//			//Console::GetSingletonPtr()->print("Vel m_x(%f) m_y(%f)", m_velocity.m_x , m_velocity.m_y);
//
//		}
//
//		SpriteComponent* pSprite = component_cast<SpriteComponent>(GetOwner());
//		pSprite->SetCurrentState(m_currentState);
//		pSprite->SetCurrentDirection(m_currentDirection);
//	}
//		SetIsSupported(false, m_floor);
//		m_isClimping = false;
//		break;
//	default:
//		break;
//	}
//}