#include "PlayerMovementComponent.h"

#include "PlayerMovementComponent.h"
#include "Framework\Utilities\Timer.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\GameObjects\Components\StaticComponent.h"
#include "Framework\Input\Input.h"
#include "Framework\Utilities\Console.h"
#include "Framework\Utilities\FPSCounter.h"
#include "GameResources.h"
using namespace Framework;


PlayerMovementComponent::PlayerMovementComponent(GameObject* pOwner)
	: MovementComponent(pOwner)
	, HealthFunction()
	, TimingFunction()
	, m_isClimping(false)
	, m_isJumping(false)
	, m_isKeyPress(false)
{
	
}

PlayerMovementComponent::~PlayerMovementComponent()
{
	MovementComponent::~MovementComponent();
}

void PlayerMovementComponent::Initialize()
{
	Framework::AttachComponentEvent(Events::COM_UPDATE_EVENT, GetOwner(), *this);
}

void PlayerMovementComponent::HandleEvent(Framework::Event* pEvent)
{
	MovementComponent::HandleEvent(pEvent);
}

void PlayerMovementComponent::PollInputUpdate()
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

void PlayerMovementComponent::BehaviorUpdate()
{
	TimingFunction::UpdateTimingFunc();
	HealthFunction::UpdateHealthFunc();

	//Console::GetSingletonPtr()->print("Timing Function update meet (%d)!", IsUpdate());

	//Console::GetSingletonPtr()->print("Player position (%f,%f)", position.m_x, position.m_y);
	//Console::GetSingletonPtr()->print("Offset Resolve left(%f) right(%f) top(%f) bottom(%f)", m_resolveOffset[CollisionDirections::LEFT], m_resolveOffset[CollisionDirections::RIGHT], m_resolveOffset[CollisionDirections::TOP], m_resolveOffset[CollisionDirections::BOTTOM]);
	//Console::GetSingletonPtr()->print("Offset left(%f) right(%f) top(%f) bottom(%f)", m_offset[CollisionDirections::LEFT], m_offset[CollisionDirections::RIGHT], m_offset[CollisionDirections::TOP], m_offset[CollisionDirections::BOTTOM]);
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
			
			if (m_collisionDirection == CollisionDirections::TOP)
			{
				float floor_y = pStaticComponent->GetRenderable().GetTransform().GetTranslation().m_y;
				SetIsSupported(true, floor_y);
			}

			//Resolve
			ResolveCollisionRun();
		}
	}

	if (pData->m_pCollider->GetResId() == GameResources::NPC_BULLET)
	{
		Damage(10);
	}
}








