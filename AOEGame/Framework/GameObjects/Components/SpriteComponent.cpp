#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "../../Utilities/Timer.h"
#include "../../Utilities/Console.h"
namespace Framework
{
	SpriteComponent::SpriteComponent(GameObject* pOwner)
		: RenderableComponent(pOwner)
		, m_animationList()
		, m_keypressed(false)
		, m_curState(SpriteStates::STATIONARY)
		, m_curDirection(SpriteDirections::RIGHT)
		, m_velocity(0.0f, 0.0f, 0.0f)
	{
	}

	SpriteComponent::~SpriteComponent()
	{
	}

	void SpriteComponent::RegisterState(int state, SpriteDirections direction, Animation* anim)
	{
		int stateCode = state + direction;

		if (m_animationList.find(stateCode) == m_animationList.end())
		{
			m_animationList.insert(AnimationMap::value_type(stateCode, anim));
		}
	}

	void SpriteComponent::RegisterState(int state, Animation* anim)
	{
		int stateCode = state;

		if (m_animationList.find(stateCode) == m_animationList.end())
		{
			m_animationList.insert(AnimationMap::value_type(stateCode, anim));
		}
	}

	void SpriteComponent::RemoveState(int state, SpriteDirections direction)
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

	void SpriteComponent::RemoveStates(int state)
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

	void SpriteComponent::SetCurrentState(int state)
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
		
		Framework::AttachComponentEvent(Events::COM_POST_UPDATE_EVENT, this->GetOwner(), *this);
		Framework::AttachComponentEvent(Events::COM_RENDER_EVENT, this->GetOwner(), *this);
	}

	void SpriteComponent::HandleEvent(Event* pEvent)
	{
		RenderableComponent::HandleEvent(pEvent);

		switch (pEvent->GetID())
		{
		case Events::COM_RENDER_EVENT:
			Renderer::GetSingletonPtr()->AddRenderable(&m_renderable);
			break;

		case Events::COM_POST_UPDATE_EVENT:
		default:
			m_animIt = m_animationList.find(m_curState + m_curDirection);
			if (m_animIt != m_animationList.end())
			{
				m_renderable.SetTextureRegion(m_animationList[m_curState + m_curDirection]->Next());
			}
			else
			{
				m_animIt = m_animationList.find(m_curState);
				if (m_animIt != m_animationList.end())
					m_renderable.SetTextureRegion(m_animationList[m_curState]->Next());
			}

			Vector3 boundMin = GetBoundMin();
			Vector3 boundMax = GetBoundMax();
			break;
		}
	}

}
