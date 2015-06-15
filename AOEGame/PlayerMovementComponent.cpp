#include "PlayerMovementComponent.h"
#include "Framework\Utilities\Timer.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\GameObjects\Components\StaticComponent.h"
#include "Framework\GameObjects\Components\CollisionComponent.h"
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
	, m_vectorOffset(0.0f, 0.0f, 0.0f)
	, m_isClimping(false)
	, m_isJumping(false)
	, m_isKeyPress(false)
{
	
}

PlayerMovementComponent::~PlayerMovementComponent()
{
}

void PlayerMovementComponent::Initialize()
{
	//Framework::AttachEvent(Events::SCE_KEY_DOWN_EVENT, *this);
	//Framework::AttachEvent(Events::SCE_KEY_UP_EVENT, *this);
	Framework::AttachComponentEvent(Events::COM_UPDATE_EVENT, GetOwner(), *this);
}

void PlayerMovementComponent::HandleEvent(Event* pEvent)
{
	switch (pEvent->GetID())
	{
	case Events::COM_UPDATE_EVENT:
	{
		_ProcessPollInput();
		
		

		TransformComponent* pOwnerTransformComponent = component_cast<TransformComponent>(GetOwner());
		assert(pOwnerTransformComponent);
		CollisionComponent* pOwnerCollisionComponent = component_cast<CollisionComponent>(GetOwner());
		assert(pOwnerCollisionComponent);
		
		if (pOwnerTransformComponent)
		{
			const Vector3& position = pOwnerTransformComponent->GetTransform()->GetTranslation();

			static const float ACCELERATION_MINIMUM = -20.0f;
			bool falling = m_acceleration.m_y < ACCELERATION_MINIMUM;//EPT_SILON

			Vector3 translation = m_velocity;
			translation.Multiply(Timer::GetSingleton().GetTimeSim());
			translation.Add(position);
			
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

			/*Console::GetSingletonPtr()->print("Offset floor (%f)", offset);
			if (m_isSupported && falling && m_vectorOffset.m_y > -25.0f)
			{
				translation.m_y -= m_vectorOffset.m_y;
				m_onFloor = true;
			}
			else
			{
				m_onFloor = false;
			}*/
		
			pOwnerTransformComponent->GetTransform()->SetTranslation(translation);

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

			Console::GetSingletonPtr()->print("Offset Vector m_x(%f) m_y(%f) m_z(%f)", m_vectorOffset.m_x, m_vectorOffset.m_y, m_vectorOffset.m_z);
			//Console::GetSingletonPtr()->print("Falling falling (%d) && On Floor(%d)", falling, m_onFloor);

			//Console::GetSingletonPtr()->print("Player bound min m_y (%f)", pOwnerCollisionComponent->GetAABBMin().m_y);
			Console::GetSingletonPtr()->print("Player position (%f,%f)", position.m_x, position.m_y);
			Console::GetSingletonPtr()->print("Is Climbing (%d)", m_isClimping);
			Console::GetSingletonPtr()->print("Is Supported (%d)", m_isSupported);
			Console::GetSingletonPtr()->print("Floor (%f)", m_floor);
			Console::GetSingletonPtr()->print("Is Jumping (%d)", m_isJumping);
			Console::GetSingletonPtr()->print("On Floor (%d)", m_onFloor);
			//Console::GetSingletonPtr()->print("Anim (%f)", Timer::GetSingletonPtr()->GetAnim());
			//Console::GetSingletonPtr()->print("Timer total %f", Timer::GetSingletonPtr()->GetTimeTotal());
			//Console::GetSingletonPtr()->print("Offset left(%f) right(%f) top(%f) bottom(%f)", m_offset[3], m_offset[1], m_offset[0], m_offset[2]);
			//Console::GetSingletonPtr()->print("Accel m_x(%f) m_y(%f)", m_acceleration.m_x ,m_acceleration.m_y);
			//Console::GetSingletonPtr()->print("Vel m_x(%f) m_y(%f)", m_velocity.m_x , m_velocity.m_y);
			
		}
		
		SpriteComponent* pSprite = component_cast<SpriteComponent>(GetOwner());
		pSprite->SetCurrentState(m_currentState);
		pSprite->SetCurrentDirection(m_currentDirection);
	}
		SetIsSupported(false, m_floor);
		m_isClimping = false;
		break;
	default:
		break;
	}
}

void PlayerMovementComponent::_ProcessPollInput()
{
	m_isKeyPress = false;
	bool isMoveLeftRight = false;
	

	// PART1: Change states based on key input
	if (m_isClimping)
	{
		m_currentState = SpriteStates::CLIMBING;
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
	else if (m_currentState == SpriteStates::CLIMBING)
	{
		if (IS_KEYDOWN(DIK_UP))
		{
			m_velocity.m_y = 100.0f;
			m_currentDirection = (m_currentDirection == SpriteDirections::LEFT) ? SpriteDirections::RIGHT : SpriteDirections::LEFT;
		}
		else if (IS_KEYDOWN(DIK_DOWN))
		{
			if (!m_onFloor)
				m_velocity.m_y = -100.0f;
			m_currentDirection = (m_currentDirection == SpriteDirections::LEFT) ? SpriteDirections::RIGHT : SpriteDirections::LEFT;
		}
		else
			m_velocity.m_y = 0.0f;
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

void PlayerMovementComponent::HandleCollision(CollisionEventData* pData)
{
	StaticComponent* pStaticComponent = component_cast<StaticComponent>(pData->m_pCollider);
	// We're colliding with an static object
	if (pStaticComponent)
	{
		CollisionComponent* pColliderCollisionComponent = component_cast<CollisionComponent>(pData->m_pCollider);
		assert(pColliderCollisionComponent);
		CollisionComponent* pObjectCollisionComponent = component_cast<CollisionComponent>(GetOwner());
		assert(pObjectCollisionComponent);


		Vector3 minAABBObject = pObjectCollisionComponent->GetAABBMin();
		Vector3 maxAABBObject = pObjectCollisionComponent->GetAABBMax();
		Vector3 minAABBCollider = pColliderCollisionComponent->GetAABBMin();
		Vector3 maxAABBCollider = pColliderCollisionComponent->GetAABBMax();

		m_offset[0] = pObjectCollisionComponent->GetAABBMin().m_y - pColliderCollisionComponent->GetAABBMax().m_y;//TOP
		m_offset[1] = pObjectCollisionComponent->GetAABBMin().m_x - pColliderCollisionComponent->GetAABBMax().m_x;//RIGHT
		m_offset[2] = pColliderCollisionComponent->GetAABBMin().m_y - pObjectCollisionComponent->GetAABBMax().m_y;//BOTTOM
		m_offset[3] = pColliderCollisionComponent->GetAABBMin().m_x - pObjectCollisionComponent->GetAABBMax().m_x;//LEFT

		if ((m_offset[0] > -5.0f && m_offset[1] > -5.0f)
			|| (m_offset[0] > -5.0f && m_offset[3] > -5.0f))
		{
			return;
		}

		int smallest = INT_MIN, idx = -1;
		for (int i = 0; i < 4; i++) {
			if (m_offset[i] > smallest) {
				smallest = m_offset[i];
				idx = i;
			}
		}



		if (pStaticComponent->GetStaticObjectType() == ObjectTypes::STAIRWAY_OBJECT)
		{
			if (abs(m_offset[idx]) > 30.0f)
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


		if (idx == 0 && m_acceleration.m_y < -25.0f)//TOP
		{
			m_vectorOffset.m_y = m_offset[0];
			float floor_y = pStaticComponent->GetRenderable().GetTransform().GetTranslation().m_y;
			SetIsSupported(true, floor_y);

		}
		else if (idx == 3)//LEFT
		{
			m_vectorOffset.m_x = -m_offset[3];
			m_transform->GetTranslation().m_x -= m_vectorOffset.m_x;
		}
		else if (idx == 1)//RIGHT
		{
			m_vectorOffset.m_x = m_offset[1];
			m_transform->GetTranslation().m_x -= m_vectorOffset.m_x;
		}
		else if (idx == 2)//BOTTOM
		{
			m_vectorOffset.m_y = m_offset[2];
			m_transform->GetTranslation().m_y += m_vectorOffset.m_y;
			m_velocity.m_y = 0;
		}


	}

	SpriteComponent* pBulletComponent = component_cast<SpriteComponent>(pData->m_pCollider);
	if (pBulletComponent)
	{
   		int k = 3;
	}
}