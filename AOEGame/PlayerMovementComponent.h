#ifndef __PLAYERMOVEMENTCOMPONENT_H__
#define	__PLAYERMOVEMENTCOMPONENT_H__

#include "Framework\Application\Context.h"
#include "Framework\GameObjects\GameObject.h"
#include "Framework\GameObjects\Components\TransformComponent.h"
#include "Framework\EventManager\EventHandler.h"
#include "Framework\EventManager\EventManager.h"

using namespace Framework;

	class PlayerMovementComponent
		: public TransformComponent
		, public EventHandler
	{
	private:
		//static const unsigned int s_id = ComponentIDs::PlayerMovementComponentId;
		bool			m_pressed;
		bool			m_animate;
		SpriteState		m_currentState;
		SpriteDirection	m_currentDirection;

	public:
		//static unsigned int GetId() { return s_id; }

		explicit PlayerMovementComponent(GameObject* pOwner);
		virtual ~PlayerMovementComponent();

		virtual void Initialize();

		virtual void HandleEvent(Event* pEvent);
	private:
		void _ProcessKeydownEvent(Event* pEvent);
		void _ProcessKeyupEvent(Event* pEvent);
		void _ProcessPollInput();
	};


#endif