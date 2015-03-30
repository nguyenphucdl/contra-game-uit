#include "PlayerMovementComponent.h"
#include "Framework\Utilities\Timer.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\Input\Input.h"
using namespace Framework;


PlayerMovementComponent::PlayerMovementComponent(GameObject* pOwner)
	: TransformComponent(pOwner)
	, m_pressed(false)
	, m_animate(true)
	, m_currentState(SpriteState::MOVELEFT)
	, m_currentDirection(SpriteDirection::LEFT)
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
		pSprite->UpdateState(m_currentState);

		if (m_pressed && m_animate)
		{
			Vector3& translation = m_transform->GetTranslation();
			translation.m_x += 50 * Timer::GetSingletonPtr()->GetTimeSim();
			pSprite->Animate();
		}
		else
		{
			pSprite->Pause();
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
		m_currentDirection = SpriteDirection::LEFT;
		m_currentState = SpriteState::MOVELEFT;
	}
	else if (IS_KEYDOWN(DIK_RIGHT))
	{
		m_currentDirection = SpriteDirection::RIGHT;
		m_currentState = SpriteState::MOVERIGHT;
	} 
	else if (IS_KEYDOWN(DIK_DOWN))
	{
		if (m_currentDirection == SpriteDirection::LEFT)
			m_currentState = SpriteState::SITLEFT;
		else
			m_currentState = SpriteState::SITRIGHT;
	}
	else
	{
		m_pressed = false;
		//Restore states
		isAnimate = false;
		if (m_currentDirection == SpriteDirection::LEFT)
			m_currentState = SpriteState::MOVELEFT;
		else
			m_currentState = SpriteState::MOVERIGHT;
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