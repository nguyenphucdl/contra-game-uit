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
		case Events::POST_UPDATE_EVENT:
		{
			TransformComponent* pTransformComponent = component_cast<TransformComponent>(m_attachObject);
			if (pTransformComponent)
			{
				Transform* transform = pTransformComponent->GetTransform();
				Vector3& translation = transform->GetTranslation();
					
				Renderer::GetSingletonPtr()->GetCamera().SetViewTranslate(&translation);
			}
		}
			break;
		default:
			break;
		}
	}
}