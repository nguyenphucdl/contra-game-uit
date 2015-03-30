#ifndef __SPRITECOMPONENT_H__
#define	__SPRITECOMPONENT_H__
#include "../../Application/Context.h"
#include "../GameObject.h"
#include "RenderableComponent.h"
#include "../../EventManager/EventHandler.h"
#include "../../EventManager/EventManager.h"
#include "../Actions/Animation.h"
namespace Framework
{
	
	class SpriteComponent
		: public RenderableComponent
		, public EventHandler
	{
	private:
		static const unsigned int s_id = ComponentIDs::SpriteComponentId;

		typedef std::map<int, Animation*>			AnimationMap;
		typedef AnimationMap::iterator				AnimationMapIterator;
		AnimationMap				m_animationList;
		AnimationMapIterator		m_animIt;

		SpriteStates				m_curState;
		SpriteDirections			m_curDirection;

		bool						m_keypressed;
		//bool						m_animate;
		
	public:
		static unsigned int GetId() { return s_id; }

		explicit SpriteComponent(GameObject* pOwner);
		virtual ~SpriteComponent();


		void SetDefaultState(SpriteStates state)					{ m_curState = state; }
		void SetDefaultDirection(SpriteDirections direction)		{ m_curDirection = direction; }

		void RegisterState(SpriteStates state,SpriteDirections direction,Animation* anim);
		void RemoveState(SpriteStates state, SpriteDirections direction);
		void RemoveStates(SpriteStates state);

		void SetCurrentState(SpriteStates state);
		void SetCurrentDirection(SpriteDirections direction);


		virtual void Initialize();

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif//__TILEMAPCOMPONENT_H__