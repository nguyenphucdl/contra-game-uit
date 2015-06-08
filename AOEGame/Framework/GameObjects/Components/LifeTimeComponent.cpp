#include"LifeTimeComponent.h"

namespace Framework
{
	LifeTimeComponent::LifeTimeComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_eslapse(0.0f)
		, m_lifeTime(0.0f)
		, m_isDead(false)
		, m_start(false)
	{

	}

	LifeTimeComponent::~LifeTimeComponent()
	{

	}

	void LifeTimeComponent::Initialize()
	{
		Framework::AttachComponentEvent(Events::COM_UPDATE_EVENT, GetOwner(), *this);
	}

	void LifeTimeComponent::HandleEvent(Event* pEvent)
	{
		switch (pEvent->GetID())
		{
		case Events::COM_UPDATE_EVENT:
		{
			if (m_start)
			{
				m_eslapse += Timer::GetSingletonPtr()->GetTimeSim();

				if (m_eslapse > m_lifeTime)
					m_isDead = true;
			}
		}
			break;
		}
	}
}