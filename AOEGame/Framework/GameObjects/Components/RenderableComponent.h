#ifndef __RENDERABLECOMPONENT_H__
#define __RENDERABLECOMPONENT_H__

#include "../Component.h"
#include "../../Renderer/Renderable.h"
#include "../../EventManager/EventManager.h"

namespace Framework
{
	class RenderableComponent
		: public Component
		, public EventHandler
	{
	protected:
		static const unsigned int s_id = ComponentIDs::RenderableComponentId;

		Renderable		m_renderable;

		void HandleEvent(Event* pEvent);

	public:
		static unsigned int GetId()						{ return s_id; }

		explicit RenderableComponent(GameObject* pOwner);
		virtual ~RenderableComponent();

		virtual void Initialize();

		Renderable&	GetRenderable()						{ return m_renderable; }

		void SetTransform(Transform& trans)				{ m_renderable.SetTransform(trans); }
		void SetTranslation(Vector3& translate)			{ m_renderable.SetTranslation(translate); }

		void SetRenderTransform(bool renderTrans)		{ m_renderable.SetRenderTransform(renderTrans); }
		void SetTag(std::string tagName)				{ m_renderable.SetTag(tagName); }
		std::string GetTag()							{ return m_renderable.GetTag(); }
		void SetDebug(bool debug)						{ m_renderable.SetDebug(debug); }
		bool IsDebug()									{ return m_renderable.IsDebug(); }
		void SetSize(int width, int height)				{ m_renderable.SetSize(width, height); }
		int	 GetWidth()									{ return m_renderable.GetWidth(); }
		int	 GetHeight()								{ return m_renderable.GetHeight(); }
		void SetUseBounds(bool enabled)					{ m_renderable.SetUseBounds(enabled); }
		void Show(bool visible)							{ m_renderable.Show(visible); }
		void Hide()										{ m_renderable.Hide(); }
		bool GetUseBounds()								{ return m_renderable.GetUseBounds(); }
		void SetBoundMin(const Vector3& min)			{ m_renderable.SetBoundMin(min); }
		Vector3&	GetBoundMin() 						{ return m_renderable.GetBoundMin(); }
		void SetBoundMax(const Vector3& max)			{ m_renderable.SetBoundMax(max); }
		Vector3&	GetBoundMax() 						{ return m_renderable.GetBoundMax(); }
		bool		IsDrawCenter()						{ return m_renderable.IsDrawCenter(); }
		void		SetDrawCenter(bool val)				{ m_renderable.SetDrawCenter(val); }
		const Vector3&		GetCenter()					{ return m_renderable.GetCenter(); }
		void		SetCenter(float x, float y)			{ m_renderable.SetCenter(x, y); }
		void		SetZIndex(int idx)					{ m_renderable.SetZIndex(idx); }
		int			GetZIndex()							{ return m_renderable.GetZIndex(); }

	};
}
#endif//__RENDERABLECOMPONENT_H__