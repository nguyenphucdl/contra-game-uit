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
		static const unsigned int s_id = 9;

		Vector3		m_acceleration;
		Vector3		m_velocity;

		bool		m_keyPressed;
	public:
		static unsigned int GetId() { return s_id; }

		explicit MovementComponent(Framework::GameObject* pOwner);
		virtual ~MovementComponent();

		virtual void Initialize();

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif