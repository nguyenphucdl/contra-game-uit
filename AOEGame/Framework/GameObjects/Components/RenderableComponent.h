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
		static unsigned int GetId() { return s_id; }

		explicit RenderableComponent(GameObject* pOwner);
		virtual ~RenderableComponent();

		virtual void Initialize();

		Renderable&	GetRenderable() { return m_renderable; }
	};
}
#endif//__RENDERABLECOMPONENT_H__