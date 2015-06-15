#include "RangeOfMovementComponent.h"

namespace Framework
{
	RangeOfMovementComponent::RangeOfMovementComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_objectTarget(-1)
	{
	}

	RangeOfMovementComponent::~RangeOfMovementComponent()
	{
	}

	void RangeOfMovementComponent::Initialize()
	{

	}
}