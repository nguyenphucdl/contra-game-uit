#ifndef __SPRITECOMPONENT_H__
#define	__SPRITECOMPONENT_H__
#include "../../Application/Context.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../../Renderer/Renderable.h"
#include "../../EventManager/EventHandler.h"
#include "../../EventManager/EventManager.h"
#include "../Actions/Animation.h"
namespace Framework
{
	enum SpriteDirection
	{
		LEFT = 0,
		RIGHT = 100
	};

	enum SpriteState 
	{
		MOVELEFT = SpriteDirection::LEFT,
		SITLEFT,
		MOVERIGHT = SpriteDirection::RIGHT,
		SITRIGHT,
		JUMPUP
	};
	
	class SpriteComponent
		: public Component
		, public EventHandler
	{
	private:
		static const unsigned int s_id = 4;

		typedef std::map<int, Animation*>	AnimationMap;
		typedef AnimationMap::iterator				AnimationMapIterator;
		AnimationMap			m_animationList;
		AnimationMapIterator	m_animIt;

		Renderable		m_renderable;
		SpriteState		m_curState;

		bool			m_keypressed;
		bool			m_animate;
		
	public:
		static unsigned int GetId() { return s_id; }

		explicit SpriteComponent(GameObject* pOwner);
		virtual ~SpriteComponent();

		void RegisterState(SpriteState state, Animation* anim);

		void RemoveState(SpriteState state);

		void SetDefaultState(SpriteState state) { m_curState = state; }

		//void UpdateTransform(Transform& transfrom) { m_renderable.GetTransform().Clone(transfrom); }

		Renderable&	GetRenderable() { return m_renderable; }

		virtual void Initialize();

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif//__TILEMAPCOMPONENT_H__