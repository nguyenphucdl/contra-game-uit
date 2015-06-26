#ifndef _LITTLE_POLYGOT_MOVEMENTCOMPONENT_H__
#define	_LITTLE_POLYGOT_MOVEMENTCOMPONENT_H__

#include "MovementComponent.h"


class LittlePolygotMovementComponent
	: public MovementComponent
{
private:
	


public:
	explicit LittlePolygotMovementComponent(Framework::GameObject* pOwner);
	virtual ~LittlePolygotMovementComponent();

	void Initialize();

private:
	void HandleCollision(Framework::CollisionEventData* pData);
	void HandleEvent(Framework::Event* pEvent);
	void PollInputUpdate();
	void BehaviorUpdate();
	void PostUpdate();
};

#endif