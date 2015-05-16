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
		, m_transOrigin(0.0f, 0.0f, 0.0f)
	{
		Framework::AttachEvent(Events::POST_UPDATE_EVENT, *this);
	}

	void CameraComponent::SetBound(RECT bound)
	{
		m_bound.left = bound.left;
		m_bound.right = bound.right;
		m_bound.top = bound.top;
		m_bound.bottom = bound.bottom;
	}

	void CameraComponent::SetViewportOrigin(int x, int y)
	{
		//Renderer::GetSingletonPtr()->GetCamera().SetViewPortOrigin(x, y);
		//Renderer::GetSingletonPtr()->GetCamera().ResetViewport();
	}

	void CameraComponent::SetViewportTranslate(int mx, int my)
	{
		//m_transOrigin = Vector3(mx, my, 0);
		//Renderer::GetSingletonPtr()->GetCamera().SetViewTranslate(&m_transOrigin);
	}


	CameraComponent::~CameraComponent()
	{
	}

	void CameraComponent::Initialize()
	{
		m_viewPortWidth = Renderer::GetSingletonPtr()->GetCamera().GetViewPortWidth();
		m_viewPortHeight = Renderer::GetSingletonPtr()->GetCamera().GetViewPortHeight();
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
				
				translation.m_y = 0;//phụ thuộc vào map orientation
				
				translation.Add(m_transOrigin);

				if (translation.m_x < m_bound.left)
					translation.m_x = 0;
				else if (translation.m_x > m_bound.right - m_viewPortWidth)
					translation.m_x = m_bound.right - m_viewPortWidth;
				if (translation.m_y < m_bound.top)
					translation.m_y = m_bound.top;
				else if (translation.m_y > m_bound.bottom - m_viewPortHeight)
					translation.m_y = m_bound.bottom - m_viewPortHeight;
					

				Renderer::GetSingletonPtr()->GetCamera().SetViewTranslate(&translation);
			}
		}
			break;
		default:
			break;
		}
	}
}