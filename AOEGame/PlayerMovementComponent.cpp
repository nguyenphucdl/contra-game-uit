#include "PlayerMovementComponent.h"
#include "Framework\Utilities\Timer.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\Input\Input.h"
using namespace Framework;


PlayerMovementComponent::PlayerMovementComponent(GameObject* pOwner)
	: TransformComponent(pOwner)
	, m_pressed(false)
	, m_animate(true)
	, m_currentState(SpriteStates::STATIONARY)
	, m_currentDirection(SpriteDirections::RIGHT)
{
	Framework::AttachEvent(Events::KEY_DOWN_EVENT, *this);
	Framework::AttachEvent(Events::KEY_UP_EVENT, *this);
	Framework::AttachEvent(Events::UPDATE_EVENT, *this);
}

PlayerMovementComponent::~PlayerMovementComponent()
{
}

void PlayerMovementComponent::Initialize()
{

}

void PlayerMovementComponent::HandleEvent(Event* pEvent)
{
	switch (pEvent->GetID())
	{
	case Events::KEY_DOWN_EVENT:
		break;
	case Events::KEY_UP_EVENT:
		break;
	case Events::UPDATE_EVENT:
	{
		_ProcessPollInput();

		SpriteComponent* pSprite = component_cast<SpriteComponent>(GetOwner());
		pSprite->SetCurrentState(m_currentState);
		pSprite->SetCurrentDirection(m_currentDirection);

		if (m_pressed && m_animate)
		{
			Vector3& translation = m_transform->GetTranslation();

			// Update translation
			if (m_currentState == SpriteStates::MOVE)
			{
				/*if (m_currentDirection == SpriteDirections::RIGHT)
					translation.m_x += 50 * Timer::GetSingletonPtr()->GetTimeSim();
				else if (m_currentDirection == SpriteDirections::LEFT)
					translation.m_x -= 50 * Timer::GetSingletonPtr()->GetTimeSim();*/
			}

			//pSprite->Animate();
		}
		
	}
		break;
	default:
		break;
	}
}

void PlayerMovementComponent::_ProcessPollInput()
{
	bool isAnimate = true;
	m_pressed = true;

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
	else if (IS_KEYDOWN(DIK_DOWN))
	{
		m_currentState = SpriteStates::SIT;
	}
	else
	{
		m_pressed = false;
		//Restore states
		isAnimate = false;
		m_currentState = SpriteStates::STATIONARY;
	}

	if (isAnimate)
		m_animate = true;
	else
		m_animate = false;
}

void PlayerMovementComponent::_ProcessKeydownEvent(Event* pEvent)
{
	
}

void PlayerMovementComponent::_ProcessKeyupEvent(Event* pEvent)
{

}