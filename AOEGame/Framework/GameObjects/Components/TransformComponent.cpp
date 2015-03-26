#include "TransformComponent.h"
#include "../GameObject.h"


namespace Framework
{
	TransformComponent::TransformComponent(GameObject* pOwner)
		:	Component(pOwner)
		,   m_transform(NULL)
	{

	}

	TransformComponent::~TransformComponent()
	{

	}

	void TransformComponent::Initialize()
	{
		
	}

	bool TransformComponent::AttachRenderableTransform(RenderableComponent *pRenderableComponent)
	{
		assert(pRenderableComponent); // Need to check runtime error and throw game exception
		SetTransform(&pRenderableComponent->GetRenderable().GetTransform());
		return true;
	}
}