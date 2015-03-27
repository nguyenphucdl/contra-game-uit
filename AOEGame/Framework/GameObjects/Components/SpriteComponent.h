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

		SpriteState					m_curState;

		bool						m_keypressed;
		bool						m_animate;
		
	public:
		static unsigned int GetId() { return s_id; }

		explicit SpriteComponent(GameObject* pOwner);
		virtual ~SpriteComponent();


		void SetDefaultState(SpriteState state) { m_curState = state; }

		void RegisterState(SpriteState state, Animation* anim);
		void RemoveState(SpriteState state);
		void UpdateState(SpriteState state);
		void Animate();
		void Reset();
		void Pause();


		virtual void Initialize();

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif//__TILEMAPCOMPONENT_H__