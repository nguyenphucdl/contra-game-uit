#ifndef __PLAYERMOVEMENTCOMPONENT_H__
#define	__PLAYERMOVEMENTCOMPONENT_H__

#include "Framework\Application\Context.h"
#include "Framework\GameObjects\GameObject.h"
#include "Framework\GameObjects\Component.h"
#include "Framework\EventManager\EventHandler.h"
#include "Framework\EventManager\EventManager.h"

using namespace Framework;

	class PlayerMovementComponent
		: public Component
		, public EventHandler
	{
	private:
		static const unsigned int s_id = ComponentIDs::PlayerMovementComponent;
	public:
		static unsigned int GetId() { return s_id; }

		explicit PlayerMovementComponent(GameObject* pOwner);
		virtual ~PlayerMovementComponent();

		virtual void Initialize();

		virtual void HandleEvent(Event* pEvent);
	};


#endif