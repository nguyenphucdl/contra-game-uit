#include "MovementComponent.h"


#include "Framework\GameObjects\Components\TransformComponent.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\Utilities\Timer.h"

namespace Framework
{
	MovementComponent::MovementComponent(Framework::GameObject* pOwner)
		: Component(pOwner)
		, m_velocity(0, 0, 0)
		, m_keyPressed(false)
		, m_move(false)
		, m_gravity(0.0f)
	{
		Framework::AttachEvent(Events::PLAYER_JUMP_EVENT, *this);
		Framework::AttachEvent(Events::UPDATE_EVENT, *this);
		Framework::AttachEvent(Events::KEY_DOWN_EVENT, *this);
		Framework::AttachEvent(Events::KEY_UP_EVENT, *this);
	}

	MovementComponent::~MovementComponent()
	{
	}

	void MovementComponent::Initialize()
	{
		
	}

	void MovementComponent::HandleEvent(Event* pEvent)
	{
		if (pEvent->GetID() == Events::PLAYER_JUMP_EVENT)
		{
			int i = 3;
		}
		else if(pEvent->GetID() == UPDATE_EVENT)
		{
			if (m_keyPressed)
			{
				if (m_move)
				{
					TransformComponent* pTransformComponent = component_cast<TransformComponent>(GetOwner());
					if (pTransformComponent)
					{
						Vector3& translation = pTransformComponent->GetTransform()->GetTranslation();
						
						translation.m_x += + m_velocity.m_x * Timer::GetSingletonPtr()->GetTimeSim();
						//translation.m_y += + m_velocity.m_y * Timer::GetSingletonPtr()->GetTimeSim();
						

						Log::info(Log::LOG_LEVEL_MEDIUM, "[MovementComponent] Move x %f\n", translation.m_x);
						Log::info(Log::LOG_LEVEL_MEDIUM, "[MovementComponent] Move y %f\n", translation.m_y);
					}
				}
			}
		}
		else if (pEvent->GetID() == Events::KEY_DOWN_EVENT)
		{
			int keyCode = (int)pEvent->GetData();

			switch (keyCode)
			case DIK_LEFT:			{

			{
				m_velocity.m_x *= (m_velocity.m_x > 0) ? -1.0f : 1.0f;
				m_move = true;
			}
				break;
			case DIK_RIGHT:
			{
				m_velocity.m_x *= (m_velocity.m_x < 0) ? -1.0f : 1.0f;
				m_move = true;
			}
				break;
			case DIK_UP:
			{
				m_velocity.m_y *= (m_velocity.m_y > 0) ? -1.0f : 1.0f;
				m_move = true;
			}
				break;
			case DIK_DOWN:
			{
				m_velocity.m_y *= (m_velocity.m_y < 0) ? -1.0f : 1.0f;
				m_move = true;
			}
				break;
			default:
				m_move = false;
				break;
			}

			m_keyPressed = true;
		}
		else if (pEvent->GetID() == Events::KEY_UP_EVENT)
		{
			m_keyPressed = false;
			m_move = false;
		}
	}
}