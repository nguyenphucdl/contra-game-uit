#include "PlayerMovementComponent.h"
#include "Framework\Utilities\Timer.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\GameObjects\Components\StaticComponent.h"
#include "Framework\Input\Input.h"
#include "Framework\Utilities\Console.h"
using namespace Framework;


PlayerMovementComponent::PlayerMovementComponent(GameObject* pOwner)
	: TransformComponent(pOwner)
	, m_pressed(false)
	, m_animate(true)
	, m_currentState(SpriteStates::STATIONARY)
	, m_currentDirection(SpriteDirections::RIGHT)
	, m_floor(100.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f, 0.0f)
	, m_isSupported(true)
{
	
}

PlayerMovementComponent::~PlayerMovementComponent()
{
}

void PlayerMovementComponent::Initialize()
{
	Framework::AttachEvent(Events::KEY_DOWN_EVENT, *this);
	Framework::AttachEvent(Events::KEY_UP_EVENT, *this);
	Framework::AttachEvent(Events::UPDATE_EVENT, *this);
	Framework::AttachEvent(Events::PLAYER_JUMP_EVENT, *this);
}

void PlayerMovementComponent::HandleEvent(Event* pEvent)
{
	switch (pEvent->GetID())
	{
	case Events::UPDATE_EVENT:
	{
		_ProcessPollInput();

		
			//Update direction
		if (m_currentState == SpriteStates::MOVE)
		{
			if (m_currentDirection == SpriteDirections::RIGHT)
				m_velocity.m_x = 50.0f;
			else if (m_currentDirection == SpriteDirections::LEFT)
				m_velocity.m_x = -50.0f;
		}
		else if (m_currentState == SpriteStates::STATIONARY)
		{
			m_velocity.m_x = 0.0f;
		}

		//Vector3& position = m_transform->GetTranslation();
		//position.m_y += 10.0f * Timer::GetSingletonPtr()->GetTimeSim();
		/*if (IS_KEYDOWN(DIK_UP))
		{
			position.m_y += 90.0f * Timer::GetSingletonPtr()->GetTimeSim();
		}
		else if (IS_KEYDOWN(DIK_DOWN))
		{
			position.m_y -= 90.0f * Timer::GetSingletonPtr()->GetTimeSim();
		}*/
		

		Vector3& position = m_transform->GetTranslation();
		bool onFloor = false;
		if (position.m_y < 0)
		{
			onFloor = true;
		}

		//Test
		//std::ostringstream os;
		//os.str("");
		//os << "Player position (" << position.m_x << "," << position.m_y << ")";
		//Console::GetSingletonPtr()->print(os.str(), 5);
		Console::GetSingletonPtr()->print("Player position (%f,%f)", position.m_x, position.m_y);
		Console::GetSingletonPtr()->print("FPS (%f)", 1.0f / Timer::GetSingletonPtr()->GetTimeSim());
		Console::GetSingletonPtr()->print("Time sim (%f)", Timer::GetSingletonPtr()->GetTimeSim());
		Console::GetSingletonPtr()->print("Anim (%f)", Timer::GetSingletonPtr()->GetAnim());
		Console::GetSingletonPtr()->print("Timer total %f", Timer::GetSingletonPtr()->GetTimeTotal());

		bool falling = m_acceleration.m_y < 0.0f;
		Vector3 translation = m_velocity;
		translation.Multiply(Timer::GetSingletonPtr()->GetTimeSim());
		translation.Add(position);
		SetTranslation(&translation);
		if (falling && translation.m_y < 0)
		{
			translation.m_y = 0;
		}


		//Log::info(Log::LOG_LEVEL_HIGHT, "[PlayerMovementComponent] Update translate %f\n", position.m_y);
		
		//m_transform->SetTranslation(translation);

		Vector3 accel = m_acceleration;
		accel.Multiply(Timer::GetSingletonPtr()->GetTimeSim());
		m_velocity.Add(accel);


		static const float GRAVITY_MULTIPLIER = 25.0f;
		static const float GRAVITY_CONSTANT = -9.8f;
		m_acceleration.m_y += GRAVITY_MULTIPLIER * GRAVITY_CONSTANT * Timer::GetSingletonPtr()->GetTimeSim();
		if (falling && onFloor)
		{
			m_acceleration.m_y = 0.0f;
			m_velocity.m_y = 0.0f;
		}
		
		
		
		SpriteComponent* pSprite = component_cast<SpriteComponent>(GetOwner());
		pSprite->SetCurrentState(m_currentState);
		pSprite->SetCurrentDirection(m_currentDirection);
	}
		break;
	case Events::PLAYER_JUMP_EVENT:
	{
		if (m_isSupported)
		{
			static const float JUMP_ACCELERATION = 80.0f;
			m_acceleration.m_y = JUMP_ACCELERATION;
			m_velocity.m_y = 130.0f;
		}
	}
		break;
	default:
		break;
	}
}

void PlayerMovementComponent::_ProcessPollInput()
{
	/*if (IS_KEYDOWN(DIK_RIGHT))
	{
		m_currentState = SpriteStates::MOVE;
		m_currentDirection = SpriteDirections::RIGHT;
		int i = 3;
	}
	else if (IS_KEYDOWN(DIK_LEFT))
	{
		m_currentState = SpriteStates::MOVE;
		m_currentDirection = SpriteDirections::LEFT;
	}*/
	//bool isAnimate = true;
	//m_pressed = true;

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
		//m_pressed = false;
		//Restore states
		//isAnimate = false;
		m_currentState = SpriteStates::STATIONARY;
	}

	if (IS_KEYDOWN(DIK_SPACE))
	{
		m_currentState = SpriteStates::JUMP;
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

	/*if (isAnimate)
		m_animate = true;
	else
		m_animate = false;*/
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
		TransformComponent* pObjectTransformComponent = component_cast<TransformComponent>(GetOwner());
		assert(pObjectTransformComponent);
		

	}
}