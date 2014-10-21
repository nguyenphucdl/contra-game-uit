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
	public:
		public:
			Matrix4		m_matrixProj;
			Matrix4		m_matrixView;
			Vector3		m_updir;

			Vector3		m_position;
			Vector3		m_target;

			float		m_nearRange;
			float		m_farRange;
			float		m_aspectRatio;
			float		m_fov;
	private:
		static const unsigned int s_id = 3;

	public:
		static unsigned int GetId() { return s_id; }

		explicit CameraComponent(GameObject* pOwner);
		virtual ~CameraComponent();

		virtual void Initialize();

		void SetFrustum(const float fov, const float aspectRatio, const float near, const float far);
		void UpdateMatrix(); 

		/* get & set functions */
		float	getNearRange()				 { return m_nearRange; }
		void	setNearRange(float val)		 { m_nearRange = val;  }
		float	getFarRange()				 { return m_farRange; }
		void	setFarRange(float val)		 { m_farRange = val;  }
		float	getAspectRatio()			 { return m_aspectRatio; }
		void	setAspectRatio(float val)	 { m_aspectRatio = val;  }
		float	getFOV()					 { return m_fov; }
		void	setFOV(float val)			 { m_fov = val;  }

		Vector3	getPosition()				 { return m_position; }
		void	setPosition(Vector3& pos)	 { m_position = pos;  }
		void	setPosition(float x, float y, float z)
		{
			m_position.m_x = x;
			m_position.m_y = y;
			m_position.m_z = z;
		}
		

		Vector3 getTarget()					 { return m_target; }
		void	setTarget(Vector3& val)		 { m_target = val; }
		void	setTarget(float x, float y, float z)
		{
			m_target.m_x = x;
			m_target.m_y = y;
			m_target.m_z = z;
		}

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif//__CAMERACOMPONENT_H__