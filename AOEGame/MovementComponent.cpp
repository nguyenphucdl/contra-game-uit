#include "MovementComponent.h"


#include "Framework\GameObjects\Components\TransformComponent.h"
#include "Framework\Utilities\Timer.h"

namespace Framework
{
	MovementComponent::MovementComponent(Framework::GameObject* pOwner)
		: Component(pOwner)
		, m_acceleration(0, 0, 0)
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
			/*Log::info(Log::LOG_LEVEL_ROOT, "[MovementComponent] JUMP_EVENT...\n");
			TransformComponent* pTransformComponent = component_cast<TransformComponent>(GetOwner());
			assert(pTransformComponent);
			if(pTransformComponent) 
			{
				static const float JUMP_ACCELERATION = 0.1f;
				m_acceleration.m_y = JUMP_ACCELERATION;
			}*/
		}
		else if(pEvent->GetID() == UPDATE_EVENT)
		{
			static const float JUMP_ACCELERATION = 105.0f;
			if (m_keyPressed)
			{
				TransformComponent* pTransformComponent = component_cast<TransformComponent>(GetOwner());
				assert(pTransformComponent);

				Vector3& translation = pTransformComponent->GetTransform().GetTranslation();
				m_acceleration.m_x = JUMP_ACCELERATION * Timer::GetSingletonPtr()->GetTimeSim();
				translation.Add(m_acceleration);
			}
		}
		else if (pEvent->GetID() == KEYDOWN_EVENT)
		{
			int keyCode = (int)pEvent->GetData();

			if (keyCode == DIK_RIGHT)
			{
				m_keyPressed = true;
			}
		}
		else if (pEvent->GetID() == KEYUP_EVENT)
		{
			int keyCode = (int)pEvent->GetData();

			if (keyCode == DIK_RIGHT)
			{
				m_keyPressed = false;
			}
		}
	}
}