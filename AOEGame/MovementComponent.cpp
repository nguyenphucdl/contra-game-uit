#include "MovementComponent.h"


#include "Framework\GameObjects\Components\TransformComponent.h"


namespace Framework
{
	MovementComponent::MovementComponent(Framework::GameObject* pOwner)
		: Component(pOwner)
		, m_acceleration(0, 0, 0)
		, m_velocity(0, 0, 0)
	{
	}

	MovementComponent::~MovementComponent()
	{
	}

	void MovementComponent::Initialize()
	{
		Framework::AttachEvent(JUMP_EVENT, *this);
		Framework::AttachEvent(UPDATE_EVENT, *this);
	}

	void MovementComponent::HandleEvent(Event* pEvent)
	{
		if(pEvent->GetID() == JUMP_EVENT)
		{
			Log::info(Log::LOG_LEVEL_ROOT, "[MovementComponent] JUMP_EVENT...\n");
			TransformComponent* pTransformComponent = component_cast<TransformComponent>(GetOwner());
			assert(pTransformComponent);
			if(pTransformComponent) 
			{
				static const float JUMP_ACCELERATION = 0.01f;
				m_acceleration.m_y = JUMP_ACCELERATION;
			}
		}
		else if(pEvent->GetID() == UPDATE_EVENT)
		{
			Log::info(Log::LOG_LEVEL_ROOT, "[MovementComponent] JUMP_EVENT acceleration %f...\n", m_acceleration.m_y);
			 TransformComponent* pTransformComponent = component_cast<TransformComponent>(GetOwner());
			 assert(pTransformComponent);

			 Vector3 translation = pTransformComponent->GetTransform().GetTranslation();
			 translation.Add(m_acceleration);

			 //D3DXVec3Add(&translation, &translation, &m_acceleration);
			 
			 pTransformComponent->GetTransform().SetTranslation(translation);
		}
	}
}