#include "CameraComponent.h"
#include "../GameObject.h"
#include "TransformComponent.h"
#include "../../EventManager/EventManager.h"
#include "../../Utilities/Timer.h"
namespace Framework
{
	CameraComponent::CameraComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_attachObject(NULL)
		, m_pressed(false)
	{
		Framework::AttachEvent(Framework::POSTUPDATE_EVENT, *this);
		Framework::AttachEvent(Framework::KEYDOWN_EVENT, *this);
		Framework::AttachEvent(Framework::KEYUP_EVENT, *this);
	}

	void CameraComponent::SetViewportOrigin(int x, int y)
	{
		Renderer::GetSingletonPtr()->SetViewportOrigin(x, y);
		Renderer::GetSingletonPtr()->ResetViewport();
	}

	CameraComponent::~CameraComponent()
	{
	}

	void CameraComponent::Initialize()
	{
		
	}

	void CameraComponent::HandleEvent(Event* pEvent)
	{
		assert(pEvent);
		switch (pEvent->GetID())
		{
		case KEYDOWN_EVENT:
			m_pressed = true;
			break;
		case KEYUP_EVENT:
			m_pressed = false;
			break;
		case POSTUPDATE_EVENT:
		{
			if (m_pressed)
			{
				TransformComponent* pTransformComponent = component_cast<TransformComponent>(m_attachObject);
				if (pTransformComponent)
				{
					Transform* transform = pTransformComponent->GetTransform();
					Vector3& translation = transform->GetTranslation();
					
					Renderer::GetSingletonPtr()->UpdateViewport(&translation);

					RECT viewport = Renderer::GetSingletonPtr()->GetViewport();

					//Log::info(Log::LOG_LEVEL_MEDIUM, "[CameraComponent] Timer at %f\n", Timer::GetSingletonPtr()->GetTimeSim());
					//Log::info(Log::LOG_LEVEL_MEDIUM, "[CameraComponent] POSTUPDATE_EVENT camera translation x %f\n", Renderer::GetSingletonPtr()->GetViewportTranslate().m_x);
				}
					
			}
		}
			break;
		default:
			break;
		}
	}
}