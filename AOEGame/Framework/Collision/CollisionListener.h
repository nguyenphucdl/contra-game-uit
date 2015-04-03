#ifndef COLLISIONLISTENER_H_
#define COLLISIONLISTENER_H_
#include "../GameObjects/GameObject.h"

namespace Framework
{
	struct CollisionEventData
	{
		GameObject* m_pCollider;
	};

	class CollisionListener
	{
	public:
		virtual void HandleCollision(CollisionEventData* pData) = 0;
	};
}
#endif