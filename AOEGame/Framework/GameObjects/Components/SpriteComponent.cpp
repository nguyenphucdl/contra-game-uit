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
		//m_renderable.SetTextureRegion(m_animationList[m_curState + m_curDirection]->Current());		

		Framework::AttachEvent(Events::SCE_POST_UPDATE_EVENT, *this);
	}

	void SpriteComponent::HandleEvent(Event* pEvent)
	{

		switch (pEvent->GetID())
		{
		case Events::SCE_POST_UPDATE_EVENT:
		default:
			m_renderable.SetTextureRegion(m_animationList[m_curState + m_curDirection]->Next());

			Vector3 boundMin = GetBoundMin();
			Vector3 boundMax = GetBoundMax();
			//Console::GetSingletonPtr()->print("Player bound min(%f, %f) max(%f,%f)", boundMin.m_x, boundMin.m_y, boundMax.m_x, boundMax.m_y);
			break;
		}
	}

}
