#include "LittlePolygotMovementComponent.h"

#include "Framework\Utilities\Timer.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\GameObjects\Components\StaticComponent.h"
#include "Framework\Input\Input.h"
#include "Framework\Utilities\Console.h"
#include "Framework\Utilities\FPSCounter.h"
#include "Framework\GameObjects\Components\BulletComponent.h"
#include "GameResources.h"

using namespace Framework;


LittlePolygotMovementComponent::LittlePolygotMovementComponent(GameObject* pOwner)
	: MovementComponent(pOwner)
	, TimingFunction()
{

}

LittlePolygotMovementComponent::~LittlePolygotMovementComponent()
{
	MovementComponent::~MovementComponent();
}

void LittlePolygotMovementComponent::Initialize()
{
	Framework::AttachComponentEvent(Events::COM_UPDATE_EVENT, MovementComponent::GetOwner(), *this);
}

void LittlePolygotMovementComponent::HandleEvent(Framework::Event* pEvent)
{
	MovementComponent::HandleEvent(pEvent);
}

void LittlePolygotMovementComponent::PollInputUpdate()
{
	
	if (IS_KEYDOWN(DIK_K))
	{
		m_velocity.m_y = 100.0f;
		m_velocity.m_x = 50.0f;
	}
}

void LittlePolygotMovementComponent::BehaviorUpdate()
{
	if (GetOwner()->GetResId() == GameResources::FIVE_STAR_SHOOTER)
	{
		int k = 3;
	}
	TimingFunction::UpdateTimingFunc();
	HealthFunction::UpdateHealthFunc();
	MovementComponent::BehaviorUpdate();
	
	
	//if (Wait(m_updateDelay, ( decision + 0.5f / 6.0f))
	if (Wait(0.25, m_updateDelay))
	{
		if (m_isSupported)
		{
			int decision = RandomInRange();
			switch (decision)
			{
			case 1:
				m_velocity.m_y = 200.0f;
				m_currentDirection = SpriteDirections::LEFT;
				m_velocity.m_x = -50.0f;
				break;
			case 2:
				m_currentDirection = SpriteDirections::RIGHT;
				m_velocity.m_y = 300.0f;
				m_velocity.m_x = 50.0f;
			case 3:
				m_velocity.m_y = 400.0f;
				break;
			default:
				break;
			}

		}
	}
	if (GetOwner()->GetResId() == GameResources::FIVE_STAR_SHOOTER)
	{
		int decision = 4;
		m_updateDelay = (float)(decision) / 6.0f;
		
		if (Wait(0.25, m_updateDelay))
		{
			decision = RandomInRange();
			switch (decision)
			{
			case 1:
				m_currentState = SpriteStates::STATIONARY;
				break;
			case 2:
				
			case 3:
				
				break;
			default:
				m_currentState = SpriteStates::FIRING;
				break;
			}
		}
	}

	if (GetOwner()->GetResId() == GameResources::LITTLE_POGOBOT)
	{
		int decision = RandomInRange();
		m_updateDelay = (float)(decision + 0.5f) / 6.0f;
		if (Wait(0.25, m_updateDelay))
		{
			if (m_isSupported)
			{
				switch (decision)
				{
				case 1:
					m_velocity.m_y = 200.0f;
					m_currentDirection = SpriteDirections::LEFT;
					m_velocity.m_x = -50.0f;
					break;
				case 2:
					m_currentDirection = SpriteDirections::RIGHT;
					m_velocity.m_y = 300.0f;
					m_velocity.m_x = 50.0f;
				case 3:
					m_velocity.m_y = 400.0f;
					break;
				default:
					break;
				}

			}
		}

		if (m_isJumping)
			m_currentState = SpriteStates::JUMP;
		else
			m_currentState = SpriteStates::STATIONARY;
	}
	
	
}

void LittlePolygotMovementComponent::PostUpdate()
{
	if (m_isJumping)
		m_currentState == SpriteStates::JUMP;
	else
		m_currentState == SpriteStates::STATIONARY;

	m_isJumping = true;
	m_currentState == SpriteStates::JUMP;

	MovementComponent::PostUpdate();
}

void LittlePolygotMovementComponent::HandleCollision(CollisionEventData* pData)
{
	MovementComponent::HandleCollision(pData);
	if (pData->m_pCollider->GetResId() == GameResources::PLAYER_BULLET)
	{
		Damage(50);
	}

	//SpriteComponent* bulletComponent = component_cast<SpriteComponent>(pData->m_pCollider);
	//if (bulletComponent)
	//{
	//	//m_velocity.m_y = 200;
	//	Damage(50);
	//}
}








