#ifndef __MOVEMENTCOMPONENT_H__
#define __MOVEMENTCOMPONENT_H__

#include "Framework\Application\Context.h"//FOR TEST ONLY

#include "Framework\GameObjects\Component.h"
#include "Framework\GameObjects\GameObject.h"
#include "Framework\EventManager\EventHandler.h"
#include "Framework\EventManager\EventManager.h"
#include "Framework\Math\Vector3.h"

namespace Framework
{
	class MovementComponent
		:	public	Framework::Component
		,	public	Framework::EventHandler
	{
	private:
		static const unsigned int s_id = ComponentIDs::MovementComponentId;

		Vector3		m_velocity;
		float		m_gravity;
		bool		m_keyPressed;
		bool		m_move;

	public:
		static unsigned int GetId() { return s_id; }

		explicit MovementComponent(Framework::GameObject* pOwner);
		virtual ~MovementComponent();

		void	SetVelocity(Vector3 vec) { m_velocity = vec; }
		void	SetVelocityX(float x) { m_velocity.m_x = x; }

		virtual void Initialize();


	private:
		virtual void HandleEvent(Event* pEvent);
	};
}
#endif