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
		, m_viewOrigin(0.0f, 0.0f, 0.0f)
		, m_transOrigin(0.0f, 0.0f, 0.0f)
		, m_isAttached(false)
	{
		
	}

	void CameraComponent::AttachObject(GameObject* gameObj)
	{
		m_attachObject = gameObj;
		m_isAttached = true;
		TransformComponent* pAttachedComponent = component_cast<TransformComponent>(gameObj);
		assert(pAttachedComponent);
		Vector3 attachedTrans = pAttachedComponent->GetTranslatiton();
		m_transOrigin.Set(attachedTrans);
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
		m_viewOrigin.m_x = x;
		m_viewOrigin.m_y = y;
	}

	CameraComponent::~CameraComponent()
	{
	}

	void CameraComponent::Initialize()
	{
		Framework::AttachEvent(Events::SCE_POST_UPDATE_EVENT, *this);

		m_transOrigin.Subtract(m_viewOrigin);//Set real trans origin
		m_viewPortWidth = Renderer::GetSingletonPtr()->GetCamera().GetViewPortWidth();
		m_viewPortHeight = Renderer::GetSingletonPtr()->GetCamera().GetViewPortHeight();
	}

	void CameraComponent::HandleEvent(Event* pEvent)
	{
		assert(pEvent);
		switch (pEvent->GetID())
		{
		case Events::SCE_POST_UPDATE_EVENT:
		{
			TransformComponent* pObjTransformComponent = component_cast<TransformComponent>(m_attachObject);
			if (pObjTransformComponent)
			{
				Transform* transform = pObjTransformComponent->GetTransform();
				Vector3& translation = transform->GetTranslation().GetInverseY();
				
				Vector3 cameraTrans = translation;
				cameraTrans.Subtract(m_transOrigin);

				cameraTrans.m_y = 0;//phụ thuộc vào map orientation
				
				//translation.Add(m_transOrigin);

				if (cameraTrans.m_x < m_bound.left)
					cameraTrans.m_x = 0;
				else if (cameraTrans.m_x > m_bound.right - m_viewPortWidth)
					cameraTrans.m_x = m_bound.right - m_viewPortWidth;
				if (cameraTrans.m_y < m_bound.top)
					cameraTrans.m_y = m_bound.top;
				else if (cameraTrans.m_y > m_bound.bottom - m_viewPortHeight)
					cameraTrans.m_y = m_bound.bottom - m_viewPortHeight;
					

				Renderer::GetSingletonPtr()->GetCamera().SetViewTranslate(&cameraTrans);
			}
		}
			break;
		default:
			break;
		}
	}
}