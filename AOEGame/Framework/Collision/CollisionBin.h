#ifndef __COLLISION_H__
#define __COLLISION_H__

#include <vector>
#include "../GameObjects/Components/CollisionComponent.h"

namespace Framework
{
	class CollisionBin
	{
	private:
		typedef std::vector<CollisionComponent*>	CollisionComponentVector;
		typedef CollisionComponentVector::iterator	CollisionComponentVectorIterator;

		CollisionComponentVector			m_collisionObjects;
		CollisionComponentVectorIterator	m_currentObject;

	public:
		CollisionBin();
		~CollisionBin();


		void			AddObject(CollisionComponent* pCollisionComponent);
		CollisionComponent* GetFirst();
		CollisionComponent* GetNext();
	};
}
#endif