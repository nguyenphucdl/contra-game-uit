#ifndef __HEALTH_BAR_COMPONENT_H__
#define __HEALTH_BAR_COMPONENT_H__

#include "../Component.h"
#include "../../Math/Vector3.h"
#include "../../Utilities/Timer.h"
#include "../../EventManager/EventHandler.h"
#include "../Components/HealthFunction.h"
#include "../Components/SpriteComponent.h"

namespace Framework
{
	class HealthBarComponent
		: public Component
		, public EventHandler
	{
	private:
		static const unsigned int s_id = ComponentIDs::HealthBarComponentId;

		HealthFunction*			m_healthFunc;
		bool					m_isHealthFuncAttached;

		SpriteComponent			m_barRenderable;
		SpriteComponent			m_healthRenderable;
		int						m_height;
		RECT					m_originHealthRegion;
		RECT					m_originBarRegion;

		virtual void Initialize();

	public:
		static unsigned int GetId() { return s_id; }
		explicit HealthBarComponent(GameObject* pOwner);
		virtual ~HealthBarComponent();

		SpriteComponent& GetBarSpriteComponent()		{ return m_barRenderable; }
		SpriteComponent& GetHealthSpriteComponent()		{ return m_healthRenderable; }
		void	SetHeight(int height)					{ m_height = height; }
		void	SetOriginHealthRegion(RECT& rect)		{ m_originHealthRegion = rect; }
		void	SetOriginBarRegion(RECT& rect)			{ m_originBarRegion = rect; }


		void AttachHealthFunc(HealthFunction* healthFunc) { m_healthFunc = healthFunc; m_isHealthFuncAttached = true; }

	protected:
		virtual void HandleEvent(Event* pEvent);
	};
}
#endif//__HEALTH_BAR_COMPONENT_H__