#include "RenderableComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"


namespace Framework
{
	RenderableComponent::RenderableComponent(GameObject* pOwner)
		:	Component(pOwner)
	{
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
	