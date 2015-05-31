#ifndef __BULLET_COMPONENT_H__
#define __BULLET_COMPONENT_H__


#include <vector>

#include "../Component.h"
#include "../../EventManager/Event.h"
#include "../../EventManager/EventHandler.h"
#include "../../EventManager/EventId.h"
#include "../../Math/Vector3.h"

namespace Framework
{
	class BulletComponent
		: public Component
		, public EventHandler
	{
	private:
		static const unsigned int s_id = ComponentIDs::BulletComponentId;

		typedef std::vector<GameObject*>	BulletVector;
		typedef BulletVector::iterator		BulletVectorIterator;

		BulletVector				m_bullets;
		BulletVector				m_bulletFiring;
		BulletVectorIterator		m_bulletIterator;

		Vector3						m_velocity;
		Vector3						m_spawnOffset;
		float						m_elapse;
		float						m_delay;

	private:
		void UpdateBullets();

	public:
		static unsigned int GetId() { return s_id; }

		explicit BulletComponent(GameObject* pOwner);
		virtual ~BulletComponent();

		virtual void Initialize();

		void AddBullet(GameObject* bullet);
		void SetVelocity(float vx, float vy)	  { m_velocity.m_x = vx; m_velocity.m_y = vy; }
		void SetSpawnOffset(float ox, float oy)   { m_spawnOffset.Set(ox, oy, 1.0f); }
		const Vector3& GetSpawnOffset()			  { return m_spawnOffset; }

		void Fire();
		void Reload();

		virtual void HandleEvent(Event* pEvent);
	};
}

#endif//__BULLET_COMPONENT_H__