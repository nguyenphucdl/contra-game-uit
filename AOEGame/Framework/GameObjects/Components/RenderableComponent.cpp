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
		assert(Renderer::GetSingletonPtr());
		Renderer::GetSingleton().AddRenderable(&m_renderable);		//[FULTURE: Add to scene grapth]
	}
}
	