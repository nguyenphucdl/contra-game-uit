#ifndef __LIFETIME_COMPONENT_H__
#define __LIFETIME_COMPONENT_H__

#include "../Component.h"
#include "../../EventManager/EventManager.h"
#include "../../Math/Vector3.h"
#include "../../Utilities/Timer.h"

namespace Framework
{
	class LifeTimeComponent
		: public Component
		, public EventHandler
	{
	private:
		static const unsigned int s_id = ComponentIDs::LifeTimeComponentId;

		float		m_eslapse;
		float		m_lifeTime;
		bool		m_isDead;
		bool		m_start;


	public:
		static unsigned int GetId() { return s_id; }

		explicit LifeTimeComponent(GameObject* pOwner);
		virtual ~LifeTimeComponent();

		bool IsDead() { return m_isDead; }
		void Reset() { m_eslapse = 0.0f; m_isDead = false; }
		void SetLifeTime(float lifeTime) { m_lifeTime = lifeTime; }
		void Start()	{ m_start = true; Reset(); }
		void Pause()	{ m_start = false; }
		virtual void Initialize();

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif//__LIFETIME_COMPONENT_H__