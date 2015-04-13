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
		, m_transOrigin(0.0f, 0.0f, 0.0f)
	{
		Framework::AttachEvent(Events::POST_UPDATE_EVENT, *this);
	}

	void CameraComponent::SetViewportOrigin(int x, int y)
	{
		Renderer::GetSingletonPtr()->GetCamera().SetViewPortOrigin(x, y);
		Renderer::GetSingletonPtr()->GetCamera().ResetViewport();
	}

	void CameraComponent::SetViewportTranslate(int mx, int my)
	{
		m_transOrigin = Vector3(mx, my, 0);
		Renderer::GetSingletonPtr()->GetCamera().SetViewTranslate(&m_transOrigin);
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
			TransformComponent* pObjTransformComponent = component_cast<TransformComponent>(m_attachObject);
			if (pObjTransformComponent)
			{
				Transform* transform = pObjTransformComponent->GetTransform();
				Vector3& translation = transform->GetTranslation().GetInverseY();

				translation.Add(m_transOrigin);

				Renderer::GetSingletonPtr()->GetCamera().SetViewTranslate(&translation);
			}
		}
			break;
		default:
			break;
		}
	}
}