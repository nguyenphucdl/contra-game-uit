#include "StaticComponent.h"

namespace Framework
{
	StaticComponent::StaticComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_bound()
	{
	}

	StaticComponent::~StaticComponent()
	{
	}

	void StaticComponent::Initialize()
	{

	}
}