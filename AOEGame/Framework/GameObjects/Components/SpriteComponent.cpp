#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "../../Utilities/Timer.h"
namespace Framework
{
	SpriteComponent::SpriteComponent(GameObject* pOwner)
		: RenderableComponent(pOwner)
		, m_animationList()
		, m_keypressed(false)
		, m_curState(SpriteStates::STATIONARY)
		, m_curDirection(SpriteDirections::RIGHT)
	{
		Framework::AttachEvent(Events::POST_UPDATE_EVENT, *this);
	}

	SpriteComponent::~SpriteComponent()
	{
	}

	void SpriteComponent::RegisterState(SpriteStates state, SpriteDirections direction, Animation* anim)
	{
		int stateCode = state + direction;

		if (m_animationList.find(stateCode) == m_animationList.end())
		{
			m_animationList.insert(AnimationMap::value_type(stateCode, anim));
		}
	}

	void SpriteComponent::RemoveState(SpriteStates state, SpriteDirections direction)
	{
		int stateCode = state + direction;

		bool exist = false;
		for (m_animIt = m_animationList.begin(); m_animIt != m_animationList.end(); m_animIt++)
		{
			int nstate = (*m_animIt).first;
			if (nstate == stateCode)
			{
				exist = true;
				break;
			}
		}
		if (exist)
			m_animationList.erase(m_animIt);
	}

	void SpriteComponent::RemoveStates(SpriteStates state)
	{
		for (m_animIt = m_animationList.begin(); m_animIt != m_animationList.end(); m_animIt++)
		{
			int nstate = (*m_animIt).first;
			if (nstate / state == 1)
			{
				m_animationList.erase(m_animIt);
				break;
			}
		}
	}

	void SpriteComponent::SetCurrentState(SpriteStates state)
	{
		m_curState = state;
	}

	void SpriteComponent::SetCurrentDirection(SpriteDirections direction)
	{
		m_curDirection = direction;
	}

	void SpriteComponent::Initialize()
	{
		RenderableComponent::Initialize();
		m_renderable.SetTextureRegion(m_animationList[m_curState + m_curDirection]->Current());		
	}

	void SpriteComponent::HandleEvent(Event* pEvent)
	{

		switch (pEvent->GetID())
		{
		case Events::POST_UPDATE_EVENT:
		default:
			m_renderable.SetTextureRegion(m_animationList[m_curState + m_curDirection]->Next());
			break;
		}
	}

}
