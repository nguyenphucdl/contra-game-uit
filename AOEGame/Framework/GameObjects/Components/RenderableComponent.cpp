#include "RenderableComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"
#include "../../EventManager/EventManager.h"

namespace Framework
{
	RenderableComponent::RenderableComponent(GameObject* pOwner)
		:	Component(pOwner)
	{
		Framework::AttachEvent(RENDER_EVENT, *this);
	}

	RenderableComponent::~RenderableComponent()
	{

	}

	void RenderableComponent::Initialize()
	{
		Log::info(Log::LOG_LEVEL_ROOT, "[RenderableComponent] Initialize...\n");

		assert(Renderer::GetSingletonPtr());
		Renderer::GetSingleton().AddRenderable(&m_renderable);
	}

	void RenderableComponent::HandleEvent(Event* pEvent)
	{
		assert(pEvent);
		if(pEvent->GetID() == RENDER_EVENT)
		{
			
		}
	}
}
	