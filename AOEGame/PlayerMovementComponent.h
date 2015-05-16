#ifndef __PLAYERMOVEMENTCOMPONENT_H__
#define	__PLAYERMOVEMENTCOMPONENT_H__

#include "Framework\Application\Context.h"
#include "Framework\GameObjects\GameObject.h"
#include "Framework\GameObjects\Components\TransformComponent.h"
#include "Framework\EventManager\EventHandler.h"
#include "Framework\Collision\CollisionListener.h"
#include "Framework\EventManager\EventManager.h"

using namespace Framework;

	class PlayerMovementComponent
		: public TransformComponent
		, public EventHandler
		, public CollisionListener
	{
	private:
		//static const unsigned int s_id = ComponentIDs::PlayerMovementComponentId;
		bool				m_pressed;
		bool				m_animate;
		SpriteStates		m_currentState;
		SpriteDirections	m_currentDirection;


		Vector3				m_velocity;
		Vector3				m_acceleration;

		float				m_floor;
		bool				m_isSupported;

	public:
		//static unsigned int GetId() { return s_id; }

		explicit PlayerMovementComponent(GameObject* pOwner);
		virtual ~PlayerMovementComponent();

		virtual void Initialize();

		virtual void HandleEvent(Event* pEvent);
		virtual void HandleCollision(CollisionEventData* pData);

	private:
		void _ProcessKeydownEvent(Event* pEvent);
		void _ProcessKeyupEvent(Event* pEvent);
		void _ProcessPollInput();

		void SetIsSupported(bool isSupported, float floor = 0.0f) { m_isSupported = isSupported; m_floor = floor; }
	};


#endif