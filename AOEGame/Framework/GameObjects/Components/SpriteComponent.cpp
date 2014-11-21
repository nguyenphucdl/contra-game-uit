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
	void SpriteComponent::SetOrigin(Vector3& origin)
	{
		m_renderable.SetOrigin(origin);
	}

	Vector3& SpriteComponent::GetOrigin()
	{
		return m_renderable.GetOrigin();
	}

	void SpriteComponent::SetRenderTransform(bool renderTrans)
	{
		m_renderable.SetRenderTransform(renderTrans);
	}

	bool SpriteComponent::GetRenderTransform()
	{
		return m_renderable.GetRenderTransform();
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
						if (m_animationList.find(SpriteState::SITLEFT) != m_animationList.end())
							m_curState = SpriteState::SITLEFT;
					}
					else
					{
						if (m_animationList.find(SpriteState::SITRIGHT) != m_animationList.end())
							m_curState = SpriteState::SITRIGHT;
					}
				}
				break;
			case DIK_RIGHT:
				{
					if (m_animationList.find(SpriteState::MOVERIGHT) != m_animationList.end())
					{
						m_curState = SpriteState::MOVERIGHT;
						m_animate = true;
					}
				
				}
				break;
			case DIK_LEFT:
				{
					if (m_animationList.find(SpriteState::MOVELEFT) != m_animationList.end())
					{
						m_curState = SpriteState::MOVELEFT;
						m_animate = true;
					}
				}
				break;
			case DIK_SPACE:
				{
					if (m_curState < SpriteDirection::RIGHT)
					{
						if (m_animationList.find(SpriteState::JUMPUPLEFT) != m_animationList.end())
							m_curState = SpriteState::JUMPUPLEFT;
					}
					else
					{
						if (m_animationList.find(SpriteState::JUMPUPRIGHT) != m_animationList.end())
							m_curState = SpriteState::JUMPUPRIGHT;
					}
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
				if (m_animationList.find(SpriteState::MOVELEFT) != m_animationList.end())
				{
					m_curState = SpriteState::MOVELEFT;
				}
			}
			else
			{
				if (m_animationList.find(SpriteState::MOVERIGHT) != m_animationList.end())
				{
					m_curState = SpriteState::MOVERIGHT;
				}
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
