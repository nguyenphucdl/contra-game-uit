#include "TransformComponent.h"

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
}