#ifndef __PLAYERMOVEMENTCOMPONENT_H__
#define	__PLAYERMOVEMENTCOMPONENT_H__

#include "MovementComponent.h"


class PlayerMovementComponent
	: public MovementComponent
{
private:
	
	bool					m_isClimping;
	bool					m_isJumping;
	bool					m_isKeyPress;


public:
	//static unsigned int GetId() { return s_id; }

	explicit PlayerMovementComponent(Framework::GameObject* pOwner);
	virtual ~PlayerMovementComponent();

	void Initialize();

private:
	void HandleCollision(Framework::CollisionEventData* pData);

	void PollInputUpdate();
	void BehaviorUpdate();
	void PostUpdate();
};


#endif