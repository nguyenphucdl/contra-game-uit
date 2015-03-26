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
		Framework::AttachEvent(Events::POST_UPDATE_EVENT, *this);
		Framework::AttachEvent(Events::KEY_DOWN_EVENT, *this);
		Framework::AttachEvent(Events::KEY_UP_EVENT, *this);
	}

	void CameraComponent::SetViewportOrigin(int x, int y)
	{
		Renderer::GetSingletonPtr()->GetCamera().SetViewPortOrigin(x, y);
		Renderer::GetSingletonPtr()->GetCamera().ResetViewport();
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
		case Events::KEY_DOWN_EVENT:
			m_pressed = true;
			break;
		case Events::KEY_UP_EVENT:
			m_pressed = false;
			break;
		case Events::POST_UPDATE_EVENT:
		{
			if (m_pressed)
			{
				TransformComponent* pTransformComponent = component_cast<TransformComponent>(m_attachObject);
				if (pTransformComponent)
				{
					Transform* transform = pTransformComponent->GetTransform();
					Vector3& translation = transform->GetTranslation();
					
					Renderer::GetSingletonPtr()->GetCamera().SetViewTranslate(&translation);

					RECT viewport = Renderer::GetSingletonPtr()->GetCamera().GetViewPort();

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