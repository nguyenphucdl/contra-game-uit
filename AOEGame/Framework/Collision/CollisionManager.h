#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

#include "../Utilities/Singleton.h"
#include <vector>
#include "CollisionBin.h"
#include "../Renderer/Renderer.h"
#include "../TileMap/TileMap.h"

namespace Framework
{
	class CollisionManager
		: public Singleton<CollisionManager>
	{
	private:
		typedef std::tr1::unordered_map<ExecutorID, CollisionBin*>				CollisionBinMap;
		typedef CollisionBinMap::iterator										CollisionBinMapIterator;

		CollisionBinMap					m_collisionBins;

		ExecutorID						m_activeExecutorId;
		ExecutorID GetActiveExecutor() { return m_activeExecutorId; };
	
	public:
		CollisionManager();
		~CollisionManager();

		void TestAgainstBin(std::vector<GameObject*>* pObjects);
		void TestAgainstBin(ExecutorID execId, GameObject* pObject);
		void TestAgainstBin(GameObject* pObject);

		bool AddCollisionBin(ExecutorID execId, CollisionBin* collisionlBin);
		void AddCollisionBinFromTileMap(TileMap* tileMap, EventExecutorAware* exec);
		void SetExecutorId(ExecutorID execId) { m_activeExecutorId = execId; }
		void SetExecutor(EventExecutorAware* exec) { SetExecutorId(exec->GetExecutorId()); };

		//std::vector<GameObject*>* GetCurrentObjectList();
		void GetCurrentObjectList(std::vector<GameObject*>* objList);
	};

	inline void CollisionManager::TestAgainstBin(std::vector<GameObject*>* pObjects)
	{
		std::vector<GameObject*>::iterator it;
		for (it = pObjects->begin(); it != pObjects->end(); it++)
		{
			CollisionManager::TestAgainstBin(*it);
		}
	}

	inline void CollisionManager::TestAgainstBin(GameObject* pObject)
	{
		TestAgainstBin(GetActiveExecutor(), pObject);
	}

	inline void CollisionManager::GetCurrentObjectList(std::vector<GameObject*>* objList)
	{
		assert(objList);
		CollisionBinMapIterator result = m_collisionBins.find(GetActiveExecutor());
		if (result != m_collisionBins.end())
		{
			CollisionBin* collisionBin = result->second;

			RECT viewport = Renderer::GetSingletonPtr()->GetCamera().GetViewPort();
			Rect range = Rect(viewport.left, viewport.top, viewport.right - viewport.left, viewport.bottom - viewport.top);

			collisionBin->QueryRange(range);
			std::vector<GameObject*>* objectListResult = collisionBin->GetCurrentObjectList();
			objList->clear();
			objList->insert(objList->begin(), objectListResult->begin(), objectListResult->end());
		}
	}
}
#endif