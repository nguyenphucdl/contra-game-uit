#ifndef __CAMERACOMPONENT_H__
#define __CAMERACOMPONENT_H__

#include "../Component.h"
#include "../../EventManager/Event.h"
#include "../../EventManager/EventHandler.h"
#include "../../Renderer/Renderer.h"
#include "../../Math/Vector3.h"
#include "../../Math/Matrix4.h"


namespace Framework
{
	class CameraComponent
		:	public Component
		,	public EventHandler
	{		
	private:
		static const unsigned int s_id = ComponentIDs::CameraComponentId;

		GameObject*		m_attachObject;
		Vector3			m_viewOrigin;
		Vector3			m_transOrigin;
		RECT			m_bound;
		int				m_viewPortWidth;
		int				m_viewPortHeight;

		bool			m_pressed;
		bool			m_isAttached;

		virtual void Initialize();

	public:
		static unsigned int GetId() { return s_id; }

		explicit CameraComponent(GameObject* pOwner);
		virtual ~CameraComponent();

		void	SetBound(RECT bound);


		void	SetViewportOrigin(int x, int y);

		void	AttachObject(GameObject* gameObj);
		GameObject* GetAttachObject()				{ return m_attachObject; }

		virtual void HandleEvent(Event* pEvent);
	};

	inline void CameraComponent::SetViewportOrigin(int x, int y)
	{
		m_viewOrigin.m_x = x;
		m_viewOrigin.m_y = y;
	}

	inline void CameraComponent::SetBound(RECT bound)
	{
		m_bound.left = bound.left;
		m_bound.right = bound.right;
		m_bound.top = bound.top;
		m_bound.bottom = bound.bottom;
	}
}
#endif//__CAMERACOMPONENT_H__