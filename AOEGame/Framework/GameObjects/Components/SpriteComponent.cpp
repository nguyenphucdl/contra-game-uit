#include "SpriteComponent.h"
#include "TransformComponent.h"
namespace Framework
{
	SpriteComponent::SpriteComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_animationList()
		, m_keypressed(false)
		, m_animate(false)
	{
		Framework::AttachEvent(JUMP_EVENT, *this);
		Framework::AttachEvent(UPDATE_EVENT, *this);
		Framework::AttachEvent(KEYDOWN_EVENT, *this);
		Framework::AttachEvent(KEYUP_EVENT, *this);
		Framework::AttachEvent(RENDER_EVENT, *this);
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

	void SpriteComponent::Initialize()
	{
		m_renderable.SetTextureRegion(m_animationList[m_curState]->Current());

		assert(Renderer::GetSingletonPtr());
		Renderer::GetSingleton().AddRenderable(&m_renderable);
	}

	void SpriteComponent::HandleEvent(Event* pEvent)
	{
		switch (pEvent->GetID())
		{
		case KEYDOWN_EVENT:
		{
			int keyCode = (int)pEvent->GetData();

			switch (keyCode)
			{
			case DIK_DOWN:
				{
					if (m_curState < SpriteDirection::RIGHT)
					{
						m_curState = SpriteState::SITLEFT;
					}
					else
					{
						m_curState = SpriteState::SITRIGHT;
					}
				}
				break;
			case DIK_RIGHT:
				{
				m_curState = SpriteState::MOVERIGHT;
				m_animate = true;
				}
				break;
			case DIK_LEFT:
				{
				m_curState = SpriteState::MOVELEFT;
				m_animate = true;
				}
				break;
			default:
				break;
			}

			m_keypressed = true;
		}
			break;
		case KEYUP_EVENT:
		{
			if (m_curState < SpriteDirection::RIGHT)
			{
				m_curState = SpriteState::MOVELEFT;
			}
			else
			{
				m_curState = SpriteState::MOVERIGHT;
			}
			m_keypressed = false;
			m_animate = false;
		}
			break;
		case UPDATE_EVENT:
		{
			if (m_keypressed && m_animate)
				m_renderable.SetTextureRegion(m_animationList[m_curState]->Next());
		}
			break;
		case RENDER_EVENT:
		{
			m_renderable.SetTextureRegion(m_animationList[m_curState]->Current());
		}
			break;
		default:
			break;
		}
	}

}
