#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

#include "../Utilities/Singleton.h"
#include <vector>
#include "CollisionBin.h"

namespace Framework
{
	class CollisionManager
		: public Singleton<CollisionManager>
	{
	private:
		typedef std::vector<CollisionBin>	CollisionBinVector;

		CollisionBinVector					m_collisionBins;
	
	public:
		CollisionManager();
		~CollisionManager();

		void AddCollisionBin();
		void AddObjectToBin(const unsigned int binIndex, CollisionComponent* pObject);
		void TestAgainstBin(const unsigned int binIndex, CollisionComponent* pObject);
	};
}
#endif