#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

#include "../Utilities/Singleton.h"
#include <vector>
#include "CollisionBin.h"
#include "../TileMap/TileMap.h"

namespace Framework
{
	class CollisionManager
		: public Singleton<CollisionManager>
	{
	private:
		typedef std::tr1::unordered_map<ExecutorID, CollisionBin*>					CollisionBinMap;
		typedef CollisionBinMap::iterator							CollisionBinMapIterator;

		CollisionBinMap					m_collisionBins;

		ExecutorID						m_activeExecutorId;
		ExecutorID GetActiveExecutor() { return m_activeExecutorId; };
	
	public:
		CollisionManager();
		~CollisionManager();

		void TestAgainstBin(ExecutorID execId, GameObject* pObject);
		void TestAgainstBin(GameObject* pObject);

		bool AddCollisionBin(ExecutorID execId, CollisionBin* collisionlBin);
		void AddCollisionBinFromTileMap(TileMap* tileMap, EventExecutorAware* exec);
		void SetExecutorId(ExecutorID execId) { m_activeExecutorId = execId; }
		void SetExecutor(EventExecutorAware* exec) { SetExecutorId(exec->GetExecutorId()); };

		std::vector<GameObject*>* GetCurrentObjectList();
	};
}
#endif