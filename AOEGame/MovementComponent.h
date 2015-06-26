#ifndef __MOVEMENTCOMPONENT_H__
#define __MOVEMENTCOMPONENT_H__

#include "Framework\Application\Context.h"
#include "Framework\GameObjects\GameObject.h"
#include "Framework\GameObjects\Components\TransformComponent.h"
#include "Framework\EventManager\EventHandler.h"
#include "Framework\Collision\CollisionListener.h"
#include "Framework\GameObjects\Components\CollisionComponent.h"
#include "Framework\EventManager\EventManager.h"

enum CollisionDirections
{
	TOP,
	RIGHT,
	BOTTOM,
	LEFT,
	NONE
};

class MovementComponent
	:   public	Framework::TransformComponent
	,   public	Framework::EventHandler
	,   public  Framework::CollisionListener
{
protected:

	Framework::SpriteStates		m_currentState;
	Framework::SpriteDirections	m_currentDirection;

	Framework::Vector3			m_velocity;
	Framework::Vector3			m_acceleration;

	float					m_floor;
	bool					m_onFloor;
	bool					m_isJumping;
	bool					m_isSupported;

	//ScanCollisionRun properties
	float					m_offset[4];
	float					m_resolveOffset[4];
	CollisionDirections		m_collisionDirection;

public:
	explicit MovementComponent(Framework::GameObject* pOwner);
	virtual ~MovementComponent();

	
	virtual void Initialize();


protected:

	void HandleEvent(Framework::Event* pEvent);
	void HandleCollision(Framework::CollisionEventData* pData);

	virtual void ScanCollisionRun(Framework::CollisionComponent* pObject, Framework::CollisionComponent* pTarget, float epsilon = 5.0f);
	virtual void ResolveCollisionRun();
	virtual void PostUpdate();
	virtual void BehaviorUpdate() {};
	virtual void PollInputUpdate() {};

	void SetIsSupported(bool isSupported, float floor = 0.0f) { m_isSupported = isSupported; m_floor = floor; }
};
#endif