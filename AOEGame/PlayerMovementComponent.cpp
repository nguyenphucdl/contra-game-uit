#include "PlayerMovementComponent.h"
#include "Framework\Utilities\Timer.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\GameObjects\Components\StaticComponent.h"
#include "Framework\GameObjects\Components\CollisionComponent.h"
#include "Framework\Input\Input.h"
#include "Framework\Utilities\Console.h"
using namespace Framework;


PlayerMovementComponent::PlayerMovementComponent(GameObject* pOwner)
	: TransformComponent(pOwner)
	, m_currentState(SpriteStates::STATIONARY)
	, m_currentDirection(SpriteDirections::RIGHT)
	, m_floor(100.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f, 0.0f)
	, m_isSupported(true)
	, m_vectorOffset(0.0f, 0.0f, 0.0f)
{
	
}

PlayerMovementComponent::~PlayerMovementComponent()
{
}

void PlayerMovementComponent::Initialize()
{
	Framework::AttachEvent(Events::SCE_KEY_DOWN_EVENT, *this);
	Framework::AttachEvent(Events::SCE_KEY_UP_EVENT, *this);
	Framework::AttachEvent(Events::SCE_UPDATE_EVENT, *this);
}

void PlayerMovementComponent::HandleEvent(Event* pEvent)
{
	switch (pEvent->GetID())
	{
	case Events::SCE_UPDATE_EVENT:
	{
		_ProcessPollInput();
		
		//Update direction
		if (m_currentState == SpriteStates::MOVE)
		{
			if (m_isSupported)
			{
				if (m_currentDirection == SpriteDirections::RIGHT)
					m_velocity.m_x = 200.0f;
				else if (m_currentDirection == SpriteDirections::LEFT)
					m_velocity.m_x = -200.0f;
			}
		}
		else if (m_currentState == SpriteStates::STATIONARY)
		{
			m_velocity.m_x = 0.0f;
		}

		TransformComponent* pOwnerTransformComponent = component_cast<TransformComponent>(GetOwner());
		assert(pOwnerTransformComponent);
		//CollisionComponent* pOwnerCollisionComponent = component_cast<CollisionComponent>(GetOwner());
		//assert(pOwnerCollisionComponent);
		
		if (pOwnerTransformComponent)
		{
			const Vector3& position = pOwnerTransformComponent->GetTransform()->GetTranslation();

			static const float ACCELERATION_MINIMUM = -20.0f;
			bool falling = m_acceleration.m_y < ACCELERATION_MINIMUM;//EPT_SILON



			Vector3 translation = m_velocity;
			translation.Multiply(Timer::GetSingleton().GetTimeSim());
			translation.Add(position);

			
			
			
			//float offset = pOwnerCollisionComponent->GetAABBMin().m_y - m_floor;
			if (m_isSupported && falling && m_vectorOffset.m_y > -25.0f)
			{
				translation.m_y -= m_vectorOffset.m_y;
				m_onFloor = true;
			}
			else
			{
				m_floor = false;
			}
			


			pOwnerTransformComponent->GetTransform()->SetTranslation(translation);

			
			

			Timer& timer = Timer::GetSingleton();
			Vector3 accel = m_acceleration;
			accel.Multiply(timer.GetTimeSim());
			m_velocity.Add(accel);
			static const float GRAVITY_MULTIPLIER = 250.0f;
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
			//Console::GetSingletonPtr()->print("Player position (%f,%f)", position.m_x, position.m_y);
			Console::GetSingletonPtr()->print("FPS (%f)", 1.0f / Timer::GetSingletonPtr()->GetTimeSim());
			Console::GetSingletonPtr()->print("Time sim (%f)", Timer::GetSingletonPtr()->GetTimeSim());
			//Console::GetSingletonPtr()->print("Anim (%f)", Timer::GetSingletonPtr()->GetAnim());
			//Console::GetSingletonPtr()->print("Timer total %f", Timer::GetSingletonPtr()->GetTimeTotal());
			Console::GetSingletonPtr()->print("Offset left(%f) right(%f) top(%f) bottom(%f)", m_offset[3], m_offset[1], m_offset[0], m_offset[2]);

			Console::GetSingletonPtr()->print("Accel m_x(%f) m_y(%f)", m_acceleration.m_x ,m_acceleration.m_y);
			Console::GetSingletonPtr()->print("Vel m_x(%f) m_y(%f)", m_velocity.m_x , m_velocity.m_y);
			Log::info(Log::LOG_LEVEL_HIGHT,"JUMP ACCELL Y %f\n", m_acceleration.m_y);
		}
		
		


		SpriteComponent* pSprite = component_cast<SpriteComponent>(GetOwner());
		pSprite->SetCurrentState(m_currentState);
		pSprite->SetCurrentDirection(m_currentDirection);
	}
		SetIsSupported(false);
		break;
	default:
		break;
	}
}

void PlayerMovementComponent::_ProcessPollInput()
{
	if (IS_KEYDOWN(DIK_LEFT))
	{
		m_currentDirection = SpriteDirections::LEFT;
		m_currentState = SpriteStates::MOVE;
	}
	else if (IS_KEYDOWN(DIK_RIGHT))
	{
		m_currentDirection = SpriteDirections::RIGHT;
		m_currentState = SpriteStates::MOVE;
	} 
	else
	{
		// Restore state
		m_currentState = SpriteStates::STATIONARY;
	}

	if (IS_KEYDOWN(DIK_SPACE))
	{
		m_currentState = SpriteStates::JUMP;
		if (m_isSupported)
		{
			static const float JUMP_ACCELERATION = 180.0f;
			m_acceleration.m_y = JUMP_ACCELERATION;
			m_velocity.m_y = 350.0f;
		}
	}
	

	if (IS_KEYDOWN(DIK_F))
	{
		if (m_currentState == SpriteStates::MOVE)
			m_currentState = SpriteStates::MOVE_FIRING;
		else if (m_currentState == SpriteStates::STATIONARY)
			m_currentState = SpriteStates::STATIONARY_FIRING;
		else if (m_currentState == SpriteStates::JUMP)
			m_currentState = SpriteStates::JUMP_FIRING;
		
	}
}

void PlayerMovementComponent::_ProcessKeydownEvent(Event* pEvent)
{
	
}

void PlayerMovementComponent::_ProcessKeyupEvent(Event* pEvent)
{

} 

void PlayerMovementComponent::HandleCollision(CollisionEventData* pData)
{
	StaticComponent* pStaticComponent = component_cast<StaticComponent>(pData->m_pCollider);
	if (pStaticComponent)
	{
		// We're colliding with an static object
		CollisionComponent* pColliderCollisionComponent = component_cast<CollisionComponent>(pData->m_pCollider);
		assert(pColliderCollisionComponent);
		CollisionComponent* pObjectCollisionComponent = component_cast<CollisionComponent>(GetOwner());
		assert(pObjectCollisionComponent);


		Vector3 minAABBObject = pObjectCollisionComponent->GetAABBMin();
		Vector3 maxAABBObject = pObjectCollisionComponent->GetAABBMax();
		Vector3 minAABBCollider = pColliderCollisionComponent->GetAABBMin();
		Vector3 maxAABBCollider = pColliderCollisionComponent->GetAABBMax();

		m_offset[0] = pObjectCollisionComponent->GetAABBMin().m_y - pColliderCollisionComponent->GetAABBMax().m_y;
		m_offset[1] = pObjectCollisionComponent->GetAABBMin().m_x - pColliderCollisionComponent->GetAABBMax().m_x;
		m_offset[2] = pColliderCollisionComponent->GetAABBMin().m_y - pObjectCollisionComponent->GetAABBMax().m_y;
		m_offset[3] = pColliderCollisionComponent->GetAABBMin().m_x - pObjectCollisionComponent->GetAABBMax().m_x;

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

		if (idx == 0 && m_acceleration.m_y < -25.0f)//TOP
		{
			m_vectorOffset.m_y = m_offset[0];
			SetIsSupported(true, pColliderCollisionComponent->GetAABBMax().m_y);
			Console::GetSingletonPtr()->print("Set is supported y(%f)", pColliderCollisionComponent->GetAABBMax().m_y);
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