#ifndef __CAMERACOMPONENT_H__
#define __CAMERACOMPONENT_H__

#include "../Component.h"
#include "../../EventManager/Event.h"
#include "../../EventManager/EventHandler.h"
#include "../../EventManager/EventId.h"
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
		Vector3			m_transOrigin;

		bool			m_pressed;
	public:
		static unsigned int GetId() { return s_id; }

		explicit CameraComponent(GameObject* pOwner);
		virtual ~CameraComponent();

		virtual void Initialize();

		void	SetViewportOrigin(int x, int y);
		void	SetViewportTranslate(int mx, int my);
		void	AttachObject(GameObject* gameObj)	{ m_attachObject = gameObj; }
		GameObject* GetAttachObject()				{ return m_attachObject; }

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif//__CAMERACOMPONENT_H__