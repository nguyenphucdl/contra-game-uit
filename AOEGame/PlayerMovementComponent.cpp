#include "PlayerMovementComponent.h"
using namespace Framework;


PlayerMovementComponent::PlayerMovementComponent(GameObject* pOwner)
	: Component(pOwner)
{
	Framework::AttachEvent(Events::KEY_DOWN_EVENT, *this);
	Framework::AttachEvent(Events::KEY_UP_EVENT, *this);
}

PlayerMovementComponent::~PlayerMovementComponent()
{
}

void PlayerMovementComponent::Initialize()
{

}

void PlayerMovementComponent::HandleEvent(Event* pEvent)
{

}