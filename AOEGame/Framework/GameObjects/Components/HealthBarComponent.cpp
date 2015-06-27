#include "HealthBarComponent.h"
#include "../../EventManager/EventManager.h"

namespace Framework
{
	HealthBarComponent::HealthBarComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_healthRenderable(pOwner)
		, m_barRenderable(pOwner)
		, m_isHealthFuncAttached(false)
		, m_height(0)
	{

	}

	HealthBarComponent::~HealthBarComponent()
	{

	}

	void HealthBarComponent::Initialize()
	{
		Framework::AttachComponentEvent(Events::COM_RENDER_EVENT, GetOwner(), *this);
		Framework::AttachComponentEvent(Events::COM_POST_UPDATE_EVENT, GetOwner(), *this);

		m_barRenderable.SetCurrentState(SpriteStates::STATIONARY);
		m_healthRenderable.SetCurrentState(SpriteStates::STATIONARY);
		m_barRenderable.SetRenderTransform(false);
		m_healthRenderable.SetRenderTransform(false);

	}

	void HealthBarComponent::HandleEvent(Event* pEvent)
	{
		if (m_isHealthFuncAttached)
		{
			if (pEvent->GetID() == Events::COM_RENDER_EVENT)
			{
				RECT* healthBarRect = &m_healthRenderable.GetRenderable().GetTextureRegion()->GetRect();
				float percent = m_healthFunc->GetPercentage();
				int dmg = m_height - (m_height * percent);
				healthBarRect->top = m_originHealthRegion.top - dmg;
				healthBarRect->bottom = m_originHealthRegion.bottom - dmg;
			}
			
		
			m_barRenderable.HandleEvent(pEvent);
			m_healthRenderable.HandleEvent(pEvent);
		}

	}
}