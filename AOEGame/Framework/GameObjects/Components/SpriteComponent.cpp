#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "../../Utilities/Timer.h"
namespace Framework
{
	SpriteComponent::SpriteComponent(GameObject* pOwner)
		: RenderableComponent(pOwner)
		, m_animationList()
		, m_keypressed(false)
		, m_animate(false)
	{
		Framework::AttachEvent(Events::UPDATE_EVENT, *this);
	}

	SpriteComponent::~SpriteComponent()
	{
	}

	void SpriteComponent::RegisterState(SpriteState state, Animation* anim)
	{
		if (m_animationList.find(state) == m_animationList.end())
		{
			m_animationList.insert(AnimationMap::value_type(state, anim));
		}
		m_curState = state;
	}

	void SpriteComponent::RemoveState(SpriteState state)
	{
		bool exist = false;
		for (m_animIt = m_animationList.begin(); m_animIt != m_animationList.end(); m_animIt++)
		{
			int nstate = (*m_animIt).first;
			if (nstate == state)
			{
				exist = true;
				break;
			}
		}
		if (exist)
			m_animationList.erase(m_animIt);
	}

	void SpriteComponent::RunState(SpriteState state)
	{
		m_curState = state;
		m_animate = true;
	}
	
	void SpriteComponent::PauseState()
	{
		m_animate = false;
	}

	void SpriteComponent::Initialize()
	{
		RenderableComponent::Initialize();
		m_renderable.SetTextureRegion(m_animationList[m_curState]->Current());		
	}

	void SpriteComponent::HandleEvent(Event* pEvent)
	{
		switch (m_curState)
		{
		case SpriteState::SILENT:
			break;

		default:
			if (m_animate)
			{
				m_renderable.SetTextureRegion(m_animationList[m_curState]->Next());
			}
			break;
		}
	}

}
