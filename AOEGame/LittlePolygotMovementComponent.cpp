#include "LittlePolygotMovementComponent.h"

#include "Framework\Utilities\Timer.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\GameObjects\Components\StaticComponent.h"
#include "Framework\Input\Input.h"
#include "Framework\Utilities\Console.h"
#include "Framework\Utilities\FPSCounter.h"
#include "Framework\GameObjects\Components\BulletComponent.h"

using namespace Framework;


LittlePolygotMovementComponent::LittlePolygotMovementComponent(GameObject* pOwner)
	: MovementComponent(pOwner)
{

}

LittlePolygotMovementComponent::~LittlePolygotMovementComponent()
{
	MovementComponent::~MovementComponent();
}

void LittlePolygotMovementComponent::Initialize()
{
	Framework::AttachComponentEvent(Events::COM_UPDATE_EVENT, GetOwner(), *this);
}

void LittlePolygotMovementComponent::HandleEvent(Framework::Event* pEvent)
{
	MovementComponent::HandleEvent(pEvent);
}

void LittlePolygotMovementComponent::PollInputUpdate()
{
	
	if (IS_KEYDOWN(DIK_K))
	{
		m_velocity.m_y = 100.0f;
		m_velocity.m_x = 50.0f;
	}
}

void LittlePolygotMovementComponent::BehaviorUpdate()
{
	MovementComponent::BehaviorUpdate();
	//Console::GetSingletonPtr()->print("Player position (%f,%f)", position.m_x, position.m_y);
	//Console::GetSingletonPtr()->print("Offset Resolve left(%f) right(%f) top(%f) bottom(%f)", m_resolveOffset[CollisionDirections::LEFT], m_resolveOffset[CollisionDirections::RIGHT], m_resolveOffset[CollisionDirections::TOP], m_resolveOffset[CollisionDirections::BOTTOM]);
	//Console::GetSingletonPtr()->print("Offset left(%f) right(%f) top(%f) bottom(%f)", m_offset[CollisionDirections::LEFT], m_offset[CollisionDirections::RIGHT], m_offset[CollisionDirections::TOP], m_offset[CollisionDirections::BOTTOM]);
	if (m_isJumping)
		m_currentState = SpriteStates::JUMP;
	else
		m_currentState = SpriteStates::STATIONARY;

}

void LittlePolygotMovementComponent::PostUpdate()
{
	if (m_isJumping)
		m_currentState == SpriteStates::JUMP;
	else
		m_currentState == SpriteStates::STATIONARY;

	m_isJumping = true;
	m_currentState == SpriteStates::JUMP;

	MovementComponent::PostUpdate();
}

void LittlePolygotMovementComponent::HandleCollision(CollisionEventData* pData)
{
	MovementComponent::HandleCollision(pData);
	SpriteComponent* bulletComponent = component_cast<SpriteComponent>(pData->m_pCollider);
	if (bulletComponent)
	{
		m_velocity.m_y = 200;
	}
}








