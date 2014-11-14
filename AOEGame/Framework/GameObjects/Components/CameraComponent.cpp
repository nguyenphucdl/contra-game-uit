#include "CameraComponent.h"
#include "../GameObject.h"

namespace Framework
{
	CameraComponent::CameraComponent(GameObject* pOwner)
		: Component(pOwner)
	{

	}

	CameraComponent::~CameraComponent()
	{
	}

	void CameraComponent::Initialize()
	{
	}

	void CameraComponent::HandleEvent(Event* pEvent)
	{
		assert(pEvent);
		if(pEvent->GetID() == POSTUPDATE_EVENT)
		{
			
		}
	}
}