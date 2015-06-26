#include "RangeOfMovementComponent.h"

namespace Framework
{
	RangeOfMovementComponent::RangeOfMovementComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_objectsInRange(20)
	{
		m_objectsInRange.clear();
	}

	RangeOfMovementComponent::~RangeOfMovementComponent()
	{
	}

	void RangeOfMovementComponent::Initialize()
	{

	}
}