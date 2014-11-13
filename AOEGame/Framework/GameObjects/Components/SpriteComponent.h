#ifndef __SPRITECOMPONENT_H__
#define	__SPRITECOMPONENT_H__
#include "../Component.h"
#include "../../EventManager/EventHandler.h"
namespace Framework
{
	class SpriteComponent
		: public Component
		, public EventHandler
	{
	private:
		static const unsigned int s_id = 4;

	public:
		explicit SpriteComponent(GameObject* pOwner);
		virtual ~SpriteComponent();

		virtual void Initialize();

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif//__TILEMAPCOMPONENT_H__