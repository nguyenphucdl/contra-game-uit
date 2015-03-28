#include "PlayerMovementComponent.h"
#include "Framework\Utilities\Timer.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
using namespace Framework;


PlayerMovementComponent::PlayerMovementComponent(GameObject* pOwner)
	: TransformComponent(pOwner)
	, m_pressed(false)
	, m_animate(true)
	, m_currentState(SpriteState::MOVELEFT)
	, m_currentDirection(SpriteDirection::LEFT)
	, m_countAction(0)
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
		_ProcessKeydownEvent(pEvent);
		break;
	case Events::KEY_UP_EVENT:
		_ProcessKeyupEvent(pEvent);
		break;
	case Events::UPDATE_EVENT:
	{
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

void PlayerMovementComponent::_ProcessKeydownEvent(Event* pEvent)
{
	m_countAction++;
	if (m_countAction > 1)
		return;
	
	int keyCode = (int)pEvent->GetData();
	bool isAnimate = true;

	switch (keyCode)
	{
	case DIK_RIGHT:
		Log::info(Log::LOG_LEVEL_MEDIUM, "   [PlayerMovementComponent] DIK_RIGHT ACTION(%d)!\n", m_countAction);
		m_currentDirection = SpriteDirection::RIGHT;
		m_currentState = SpriteState::MOVERIGHT;
		
		break;
	case DIK_LEFT:
		Log::info(Log::LOG_LEVEL_MEDIUM, "   [PlayerMovementComponent] DIK_LEFT ACTION(%d)!\n", m_countAction);
		m_currentDirection = SpriteDirection::LEFT;
		m_currentState = SpriteState::MOVELEFT;
		break;

	default:
		break;
	}

	switch (keyCode)
	{
	case DIK_UP:
		Log::info(Log::LOG_LEVEL_MEDIUM, "   [PlayerMovementComponent] DIK_UP ACTION(%d)!\n", m_countAction);
		isAnimate = false;
		break;
	case DIK_DOWN:
		Log::info(Log::LOG_LEVEL_MEDIUM, "   [PlayerMovementComponent] DIK_DOWN ACTION(%d)!\n", m_countAction);
		if (m_currentDirection == SpriteDirection::LEFT)
			m_currentState = SpriteState::SITLEFT;
		else
			m_currentState = SpriteState::SITRIGHT;
		break;
	default:
		break;
	}

	if (isAnimate)
		m_animate = true;
	else
		m_animate = false;

	m_pressed = true;
}

void PlayerMovementComponent::_ProcessKeyupEvent(Event* pEvent)
{
	m_countAction--;
	m_pressed = false;

	if (m_countAction == 0)
	{
		if (m_currentDirection == SpriteDirection::LEFT)
		{
			m_currentState = SpriteState::MOVELEFT;
		}
		else
			m_currentState = SpriteState::MOVERIGHT;
	}
}