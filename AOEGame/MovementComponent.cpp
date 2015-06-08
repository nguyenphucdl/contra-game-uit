#include "MovementComponent.h"

#include "Framework\Utilities\Timer.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\GameObjects\Components\StaticComponent.h"
#include "Framework\GameObjects\Components\CollisionComponent.h"
#include "Framework\Input\Input.h"
#include "Framework\Utilities\Console.h"

using namespace Framework;

MovementComponent::MovementComponent(Framework::GameObject* pOwner)
	: Component(pOwner)
	, m_transform(NULL)
	, m_currentState(SpriteStates::STATIONARY)
	, m_currentDirection(SpriteDirections::RIGHT)
	, m_floor(100.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f, 0.0f)
	, m_isSupported(true)
	, m_vectorOffset(0.0f, 0.0f, 0.0f)
{
		
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Initialize()
{
	Framework::AttachComponentEvent(Events::COM_UPDATE_EVENT, GetOwner(), *this);
}

bool MovementComponent::AttachRenderableTransform(RenderableComponent *pRenderableComponent)
{
	assert(pRenderableComponent);
	SetTransform(&pRenderableComponent->GetRenderable().GetTransform());
	return true;
}

void MovementComponent::HandleEvent(Event* pEvent)
{
	switch (pEvent->GetID())
	{
	case Events::COM_UPDATE_EVENT:
	{
		UpdateGame();
		SpriteComponent* pSprite = component_cast<SpriteComponent>(GetOwner());
		assert(pSprite);
		pSprite->SetCurrentState(m_currentState);
		pSprite->SetCurrentDirection(m_currentDirection);
		SetIsSupported(false);
	}
		break;
	default:
		break;
	}
}

void MovementComponent::UpdateGame()
{
	const Vector3& position = this->GetTransform()->GetTranslation();

	static const float ACCELERATION_MINIMUM = -20.0f;
	bool falling = m_acceleration.m_y < ACCELERATION_MINIMUM;//EPT_SILON

	Vector3 translation = m_velocity;
	translation.Multiply(Timer::GetSingleton().GetTimeSim());
	translation.Add(position);

	if (m_isSupported && falling && m_vectorOffset.m_y > -25.0f)
	{
		translation.m_y -= m_vectorOffset.m_y;
	}

	this->GetTransform()->SetTranslation(translation);

	Vector3 accel = m_acceleration;
	accel.Multiply(Timer::GetSingletonPtr()->GetTimeSim());
	m_velocity.Add(accel);

	static const float GRAVITY_MULTIPLIER = 50.0f;
	static const float GRAVITY_CONSTANT = -9.8f;
	float dekta = GRAVITY_MULTIPLIER * GRAVITY_CONSTANT * Timer::GetSingletonPtr()->GetTimeSim();
	m_acceleration.m_y += dekta;
	if (falling && m_isSupported)
	{
		m_acceleration.m_y = 0.0f;
		m_velocity.m_y = 0.0f;
	}

}

void MovementComponent::HandleCollision(CollisionEventData* pData)
{
	StaticComponent* pStaticComponent = component_cast<StaticComponent>(pData->m_pCollider);
	if (pStaticComponent)
	{
		// We're colliding with an static object
		CollisionComponent* pColliderCollisionComponent = component_cast<CollisionComponent>(pData->m_pCollider);
		assert(pColliderCollisionComponent);
		CollisionComponent* pObjectCollisionComponent = component_cast<CollisionComponent>(GetOwner());
		assert(pObjectCollisionComponent);


		Vector3 minAABBObject = pObjectCollisionComponent->GetAABBMin();
		Vector3 maxAABBObject = pObjectCollisionComponent->GetAABBMax();
		Vector3 minAABBCollider = pColliderCollisionComponent->GetAABBMin();
		Vector3 maxAABBCollider = pColliderCollisionComponent->GetAABBMax();

		m_offset[0] = pObjectCollisionComponent->GetAABBMin().m_y - pColliderCollisionComponent->GetAABBMax().m_y;
		m_offset[1] = pObjectCollisionComponent->GetAABBMin().m_x - pColliderCollisionComponent->GetAABBMax().m_x;
		m_offset[2] = pColliderCollisionComponent->GetAABBMin().m_y - pObjectCollisionComponent->GetAABBMax().m_y;
		m_offset[3] = pColliderCollisionComponent->GetAABBMin().m_x - pObjectCollisionComponent->GetAABBMax().m_x;

		if ((m_offset[0] > -5.0f && m_offset[1] > -5.0f)
			|| (m_offset[0] > -5.0f && m_offset[3] > -5.0f))
		{
			return;
		}

		int smallest = INT_MIN, idx = -1;
		for (int i = 0; i < 4; i++) {
			if (m_offset[i] > smallest) {
				smallest = m_offset[i];
				idx = i;
			}
		}

		if (idx == 0 && m_acceleration.m_y < -25.0f)//TOP
		{
			m_vectorOffset.m_y = m_offset[0];
			SetIsSupported(true, pColliderCollisionComponent->GetAABBMax().m_y);
			Console::GetSingletonPtr()->print("Set is supported y(%f)", pColliderCollisionComponent->GetAABBMax().m_y);
		}
		else if (idx == 3)//LEFT
		{
			m_vectorOffset.m_x = -m_offset[3];
			m_transform->GetTranslation().m_x -= m_vectorOffset.m_x;
		}
		else if (idx == 1)//RIGHT
		{
			m_vectorOffset.m_x = m_offset[1];
			m_transform->GetTranslation().m_x -= m_vectorOffset.m_x;
		}
		else if (idx == 2)//BOTTOM
		{
			m_vectorOffset.m_y = m_offset[2];
			m_transform->GetTranslation().m_y += m_vectorOffset.m_y;
			m_velocity.m_y = 0;
		}
	}

	SpriteComponent* pBulletComponent = component_cast<SpriteComponent>(pData->m_pCollider);
	if (pBulletComponent)
	{
		m_velocity.m_y = 100;
		m_acceleration.m_y = 100;
	}
}
