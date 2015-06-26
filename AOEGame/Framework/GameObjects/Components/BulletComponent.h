#ifndef __BULLET_COMPONENT_H__
#define __BULLET_COMPONENT_H__


#include <vector>

#include "../Component.h"
#include "../../EventManager/Event.h"
#include "../../EventManager/EventHandler.h"
#include "../../Math/Vector3.h"
#include "../../Utilities/Enums.h"
#include "../../Collision/CollisionListener.h"

namespace Framework
{
	class BulletComponent
		: public Component
		, public EventHandler
		, public CollisionListener
	{
	private:
		static const unsigned int s_id = ComponentIDs::BulletComponentId;

		typedef std::vector<GameObject*>	BulletVector;
		typedef BulletVector::iterator		BulletVectorIterator;

		BulletVector				m_bullets;
		BulletVector				m_bulletFiring;
		BulletVectorIterator		m_bulletIterator;

		Vector3						m_velocity;
		Vector3						m_diePosition;
		Vector3						m_spawnOffset;
		float						m_elapse;
		float						m_delay;

		virtual void Initialize();
	private:
		void UpdateBullets();

	public:
		static unsigned int GetId() { return s_id; }

		explicit BulletComponent(GameObject* pOwner);
		virtual ~BulletComponent();



		void AddBullet(GameObject* bullet);
		void SetVelocity(float vx, float vy)	  { m_velocity.m_x = vx; m_velocity.m_y = vy; }
		void SetSpawnOffset(float ox, float oy)   { m_spawnOffset.Set(ox, oy, 1.0f); }
		void SetDelay(float val)				  { m_delay = val; }
		const Vector3& GetSpawnOffset()			  { return m_spawnOffset; }
		std::vector<GameObject*>* GetBullets()	  { return &m_bullets; }

		void Fire();
		void Reload();

		virtual void HandleEvent(Event* pEvent);
		virtual void HandleCollision(Framework::CollisionEventData* pData);
	};
}

#endif//__BULLET_COMPONENT_H__