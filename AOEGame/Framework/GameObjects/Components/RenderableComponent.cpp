#include "RenderableComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"
#include "../../EventManager/EventManager.h"

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
		//Framework::AttachComponentEvent(Events::COM_RENDER_EVENT, GetOwner(), *this);
	}

	void RenderableComponent::HandleEvent(Event* pEvent)
	{
		if (pEvent->GetID() == Events::COM_RENDER_EVENT)
		{
			//assert(Renderer::GetSingletonPtr());
			//Renderer::GetSingleton().AddRenderable(&m_renderable);
		}
	}
}
	