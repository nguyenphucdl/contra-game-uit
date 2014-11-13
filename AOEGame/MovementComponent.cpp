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
	{
		Framework::AttachEvent(JUMP_EVENT, *this);
		Framework::AttachEvent(UPDATE_EVENT, *this);
		Framework::AttachEvent(KEYDOWN_EVENT, *this);
		Framework::AttachEvent(KEYUP_EVENT, *this);
	}

	MovementComponent::~MovementComponent()
	{
	}

	void MovementComponent::Initialize()
	{
		
	}

	void MovementComponent::HandleEvent(Event* pEvent)
	{
		if(pEvent->GetID() == JUMP_EVENT)
		{
			
		}
		else if(pEvent->GetID() == UPDATE_EVENT)
		{
			if (m_keyPressed)
			{
				TransformComponent* pTransformComponent = component_cast<TransformComponent>(GetOwner());
				if (pTransformComponent)
				{
					Vector3& translation = pTransformComponent->GetTransform().GetTranslation();
					translation.m_x = translation.m_x + m_velocity.m_x * Timer::GetSingletonPtr()->GetTimeSim();

					Log::info(Log::LOG_LEVEL_MEDIUM, "[MovementComponent] Move x %f\n", translation.m_x);

					SpriteComponent* pSpriteComponent = component_cast<SpriteComponent>(GetOwner());
					if (pSpriteComponent)
					{
						pSpriteComponent->UpdateTransform(pTransformComponent->GetTransform());
					}
				}
			}
		}
		else if (pEvent->GetID() == KEYDOWN_EVENT)
		{
			m_keyPressed = true;
		}
		else if (pEvent->GetID() == KEYUP_EVENT)
		{
			m_keyPressed = false;
		}
	}
}