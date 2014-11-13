#include "SpriteComponent.h"
#include "TransformComponent.h"
namespace Framework
{
	SpriteComponent::SpriteComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_animationList()
		, m_keypressed(false)
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
		/*TransformComponent* pTransformComponent = component_cast<TransformComponent>(GetOwner());
		if (pTransformComponent)
		{
			m_renderable.GetTransform().Clone(pTransformComponent->GetTransform());
		}*/
		m_renderable.SetTextureRegion(m_animationList[m_curState]->Current());

		assert(Renderer::GetSingletonPtr());
		Renderer::GetSingleton().AddRenderable(&m_renderable);
		m_oldState = m_curState;
	}

	void SpriteComponent::HandleEvent(Event* pEvent)
	{
		switch (pEvent->GetID())
		{
		case KEYDOWN_EVENT:
		{
			int keyCode = (int)pEvent->GetData();
			m_oldState = m_curState;

			if (keyCode == DIK_RIGHTARROW)
			{
				Log::info(Log::LOG_LEVEL_MIN, "[SpriteComponent] MOVE RIGHT...\n");
				m_curState = SpriteState::MOVERIGHT;
			}
			else if (keyCode == DIK_LEFTARROW)
			{
				Log::info(Log::LOG_LEVEL_MIN, "[SpriteComponent] MOVELEFT...\n");
				m_curState = SpriteState::MOVELEFT;
			}
			if (keyCode == DIK_DOWNARROW)
			{
				if (m_curState < SpriteDirection::RIGHT)
				{
					m_curState = SpriteState::SITLEFT;
					Log::info(Log::LOG_LEVEL_MIN, "[SpriteComponent] KEYDOWN SITLEFT...\n");
				}
				else
				{
					m_curState = SpriteState::SITRIGHT;
					Log::info(Log::LOG_LEVEL_MIN, "[SpriteComponent] KEYDOWN SITRIGHT...\n");
				}
			}
			m_keypressed = true;
		}
			break;
		case KEYUP_EVENT:
		{
			if (m_curState < SpriteDirection::RIGHT)
			{
				m_curState = SpriteState::MOVELEFT;
				Log::info(Log::LOG_LEVEL_MIN, "[SpriteComponent] KEYUP_EVENT MOVELEFT...\n");
			}
			else
			{
				m_curState = SpriteState::MOVERIGHT;
				Log::info(Log::LOG_LEVEL_MIN, "[SpriteComponent] KEYUP_EVENT MOVERIGHT...\n");
			}
			m_keypressed = false;
		}
			break;
		case UPDATE_EVENT:
		{
			if (m_keypressed)
				m_renderable.SetTextureRegion(m_animationList[m_curState]->Next());
		}
			break;
		case RENDER_EVENT:
		{
			//Log::info(Log::LOG_LEVEL_MIN, "[SpriteComponent] RENDER_EVENT...\n");
			m_renderable.SetTextureRegion(m_animationList[m_curState]->Current());
		}
			break;
		default:
			break;
		}
	}

}
