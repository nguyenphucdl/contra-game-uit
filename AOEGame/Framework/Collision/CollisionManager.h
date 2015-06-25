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
		typedef std::vector<CollisionBin*>		CollisionBinVector;
		typedef CollisionBinVector::iterator	CollisionBinVectorIterator;

		CollisionBinVector				m_collisionBins;

		ExecutorID						m_activeExecutorId;
		ExecutorID GetActiveExecutor() { return m_activeExecutorId; };
	private:
		CollisionBin* _getCollisionBin(ExecutorID execId);

	public:
		CollisionManager();
		~CollisionManager();

		void TestAgainstBin(std::vector<GameObject*>* pObjects);
		void TestObjectAgainstBin(ExecutorID execId, GameObject* pObject);
		void TestObjectsAgainstBin(ExecutorID execId, std::vector<GameObject*>* pObjects);
		void TestAgainstBin(GameObject* pObject);		

		void AddCollisionBin(ExecutorID execId, CollisionBin* collisionlBin);
		void AddCollisionBinFromTileMap(TileMap* tileMap, EventExecutorAware* exec);
		void SetExecutorId(ExecutorID execId) { m_activeExecutorId = execId; }
		void SetExecutor(EventExecutorAware* exec) { SetExecutorId(exec->GetExecutorId()); };

		void AddUpdateObject(GameObject* object);
		void AddUpdateObjects(std::vector<GameObject*>* pObjects);
		void InitCollisionBin();

		void GetCurrentObjectList(std::vector<GameObject*>* objList);
	};

	inline void CollisionManager::TestAgainstBin(std::vector<GameObject*>* pObjects)
	{
		CollisionManager* pCollisionManager = CollisionManager::GetSingletonPtr();
		pCollisionManager->TestObjectsAgainstBin(pCollisionManager->GetActiveExecutor(), pObjects);
	}

	inline void CollisionManager::TestAgainstBin(GameObject* pObject)
	{
		CollisionManager* pCollisionManager = CollisionManager::GetSingletonPtr();
		pCollisionManager->TestObjectAgainstBin(pCollisionManager->GetActiveExecutor(), pObject);
	}

	inline void CollisionManager::GetCurrentObjectList(std::vector<GameObject*>* objList)
	{
		RECT viewport = Renderer::GetSingletonPtr()->GetCamera().GetViewPort();
		
		Rect range = Rect(viewport.left, viewport.top, viewport.right - viewport.left, viewport.bottom - viewport.top);

		m_collisionBins[m_activeExecutorId]->QueryRange(range);
		std::vector<GameObject*>* objectListResult = m_collisionBins[m_activeExecutorId]->GetCurrentObjectList();
		objList->clear();
		objList->insert(objList->begin(), objectListResult->begin(), objectListResult->end());
	}

	inline void CollisionManager::AddUpdateObject(GameObject* object)
	{
		m_collisionBins[m_activeExecutorId]->AddUpdateObject(object);
	}

	inline void CollisionManager::AddUpdateObjects(std::vector<GameObject*>* pObjects)
	{
		m_collisionBins[m_activeExecutorId]->AddUpdateObjects(pObjects);
	}

	inline void CollisionManager::InitCollisionBin()
	{
		m_collisionBins[m_activeExecutorId]->Init();
	}
}
#endif