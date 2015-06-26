#ifndef __PLAYERMOVEMENTCOMPONENT_H__
#define	__PLAYERMOVEMENTCOMPONENT_H__

#include "Framework\Application\Context.h"
#include "Framework\GameObjects\GameObject.h"
#include "Framework\GameObjects\Components\TransformComponent.h"
#include "Framework\EventManager\EventHandler.h"
#include "Framework\Collision\CollisionListener.h"
#include "Framework\GameObjects\Components\CollisionComponent.h"
#include "Framework\EventManager\EventManager.h"


class PlayerMovementComponent
	: public Framework::TransformComponent
	, public Framework::EventHandler
	, public Framework::CollisionListener
{
private:
	//static const unsigned int s_id = Framework::ComponentIDs::PlayerMovementComponentId;
	Framework::SpriteStates		m_currentState;
	Framework::SpriteDirections	m_currentDirection;


	Framework::Vector3				m_velocity;
	Framework::Vector3				m_acceleration;

	float					m_floor;
	bool					m_onFloor;
	bool					m_isSupported;
	bool					m_isClimping;
	bool					m_isJumping;
	bool					m_isKeyPress;

	//ScanCollisionRun properties
	float					m_offset[4];
	float					m_resolveOffset[4];
	CollisionDirections		m_collisionDirection;

public:
	//static unsigned int GetId() { return s_id; }

	explicit PlayerMovementComponent(Framework::GameObject* pOwner);
	virtual ~PlayerMovementComponent();

	virtual void Initialize();

	virtual void HandleEvent(Framework::Event* pEvent);
	virtual void HandleCollision(Framework::CollisionEventData* pData);

	virtual void ScanCollisionRun(Framework::CollisionComponent* pObject, Framework::CollisionComponent* pTarget, float epsilon = 5.0f);	
	virtual void ResolveCollisionRun();
	virtual void PostUpdate();

private:
	void _ProcessPollInput();

	void SetIsSupported(bool isSupported, float floor = 0.0f) { m_isSupported = isSupported; m_floor = floor; }
};


#endif