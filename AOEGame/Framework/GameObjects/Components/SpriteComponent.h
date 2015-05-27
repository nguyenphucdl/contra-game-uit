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

		int							m_curState;
		SpriteDirections			m_curDirection;

		bool						m_keypressed;
		//bool						m_animate;
		
	public:
		static unsigned int GetId() { return s_id; }

		explicit SpriteComponent(GameObject* pOwner);
		virtual ~SpriteComponent();


		void SetDefaultState(int state)					{ m_curState = state; }
		void SetDefaultDirection(SpriteDirections direction)		{ m_curDirection = direction; }

		void RegisterState(int state, SpriteDirections direction, Animation* anim);
		void RemoveState(int state, SpriteDirections direction);
		void RemoveStates(int state);

		void SetCurrentState(int state);
		int  GetCurrentState()	{ return m_curState; }
		void SetCurrentDirection(SpriteDirections direction);
		SpriteDirections GetCurrentDirection() { return m_curDirection; }

		virtual void Initialize();

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif//__TILEMAPCOMPONENT_H__