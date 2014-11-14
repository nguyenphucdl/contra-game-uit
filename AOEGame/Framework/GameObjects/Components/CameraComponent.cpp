#include "CameraComponent.h"
#include "../GameObject.h"
#include "TransformComponent.h"
#include "../../EventManager/EventManager.h"
#include "../../Utilities/Timer.h"
namespace Framework
{
	CameraComponent::CameraComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_viewPort(NULL)
		, m_attachObject(NULL)
		, m_pressed(false)
	{
		Framework::AttachEvent(Framework::POSTUPDATE_EVENT, *this);
		Framework::AttachEvent(Framework::KEYDOWN_EVENT, *this);
		Framework::AttachEvent(Framework::KEYUP_EVENT, *this);
	}

	CameraComponent::~CameraComponent()
	{
	}

	void CameraComponent::Initialize()
	{
		m_viewPort = &Renderer::GetSingletonPtr()->GetViewport();
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
					int pos = translation.m_x - 100;
					if (pos < 0)
						pos = 0;
					m_viewPort->left = pos;
					m_viewPort->right = m_viewPort->left + 640;
					Log::info(Log::LOG_LEVEL_MEDIUM, "[CameraComponent] Timer at %f\n", Timer::GetSingletonPtr()->GetTimeSim());
					Log::info(Log::LOG_LEVEL_MEDIUM, "[CameraComponent] POSTUPDATE_EVENT camera pos x %d\n", pos);
				}
			}
		}
			break;
		default:
			break;
		}
	}
}