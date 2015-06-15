#ifndef __STATICCOMPONENT_H__
#define	__STATICCOMPONENT_H__

#include "../../Application/Context.h"
#include "../../Renderer/Renderable.h"
#include "RenderableComponent.h"
#include "../../EventManager/Event.h"
#include "../../EventManager/EventHandler.h"
#include "../GameObject.h"

namespace Framework
{
	class StaticComponent
		: public RenderableComponent
	{
	private:
		static const unsigned int	s_id = ComponentIDs::StaticComponentId;

		int		m_objectType;

		virtual void Initialize();
	public:
		static unsigned int GetId() { return s_id; }

		explicit StaticComponent(GameObject* pOwner);
		virtual ~StaticComponent();

		void	SetStaticObjectType(int type) { m_objectType = type; }
		int		GetStaticObjectType() { return m_objectType; }

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif//__STATICCOMPONENT_H__