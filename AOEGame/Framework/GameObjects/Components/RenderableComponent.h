#ifndef __RENDERABLECOMPONENT_H__
#define __RENDERABLECOMPONENT_H__

#include "../Component.h"
#include "../../Renderer/Renderable.h"
#include "../../EventManager/Event.h"
#include "../../EventManager/EventHandler.h"
#include "../../EventManager/EventId.h"

namespace Framework
{
	class RenderableComponent
		: public Component
	{
	protected:
		static const unsigned int s_id = ComponentIDs::RenderableComponentId;

		Renderable		m_renderable;

	public:
		static unsigned int GetId()						{ return s_id; }

		explicit RenderableComponent(GameObject* pOwner);
		virtual ~RenderableComponent();

		virtual void Initialize();

		Renderable&	GetRenderable()						{ return m_renderable; }


		void SetOrigin(Vector3& origin)					{ m_renderable.SetOrigin(origin);	}
		void SetOrigin(int x, int y, int z)				{ m_renderable.SetOrigin(x, y, z);	}
		void SetRenderTransform(bool renderTrans)		{ m_renderable.SetRenderTransform(renderTrans); }
		void SetTag(std::string tagName)				{ m_renderable.SetTag(tagName); }
		std::string GetTag()							{ return m_renderable.GetTag(); }
		void SetDebug(bool debug)						{ m_renderable.SetDebug(debug); }
		bool IsDebug()									{ return m_renderable.IsDebug(); }
		void SetSize(int width, int height)				{ m_renderable.SetSize(width, height); }
		int	 GetWidth()									{ return m_renderable.GetWidth(); }
		int	 GetHeight()								{ return m_renderable.GetHeight(); }
		void SetUseBounds(bool enabled)					{ m_renderable.SetUseBounds(enabled); }
		bool GetUseBounds()								{ return m_renderable.GetUseBounds(); }
		void SetBoundMin(const Vector3& min)			{ m_renderable.SetBoundMin(min); }
		Vector3&	GetBoundMin() 						{ return m_renderable.GetBoundMin(); }
		void SetBoundMax(const Vector3& max)			{ m_renderable.SetBoundMax(max); }
		Vector3&	GetBoundMax() 						{ return m_renderable.GetBoundMax(); }

	};
}
#endif//__RENDERABLECOMPONENT_H__