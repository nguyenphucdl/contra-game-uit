#include "CollisionManager.h"
#include "../GameObjects/GameObject.h"
#include "../EventManager/EventManager.h"
#include "../Renderer/Renderer.h"
#include "../Utilities/FPSCounter.h"
#include "../Utilities/Console.h"
namespace Framework
{
	CollisionManager::CollisionManager()
		: m_collisionBins()
	{
	}

	CollisionManager::~CollisionManager()
	{
	}

	void CollisionManager::AddCollisionBinFromTileMap(TileMap* tileMap, EventExecutorAware* exec)
	{
		assert(tileMap);
		SetExecutor(exec);

		Quadtree* qtree = tileMap->GetQuadTree();
		ObjectHashTable* objTable = tileMap->GetOjectHashTable();
		CollisionBin* collBin = new CollisionBin(exec->GetExecutorId(), qtree, objTable);
		AddCollisionBin(exec->GetExecutorId(), collBin);
	}

	bool CollisionManager::AddCollisionBin(ExecutorID execId, CollisionBin* collisionlBin)
	{
		bool added = false;
		CollisionBinMapIterator result = m_collisionBins.find(execId);
		if (result == m_collisionBins.end())
		{
			assert(collisionlBin);
			std::pair<ExecutorID, CollisionBin*> newCollBin(execId, collisionlBin);
			std::pair<CollisionBinMapIterator, bool> addedIter = m_collisionBins.insert(newCollBin);
			added = addedIter.second;
		}
		return added;
	}

	void CollisionManager::TestAgainstBin(ExecutorID execId, GameObject* pObject)
	{
		CollisionComponent* pObjectCollisionComponent = component_cast<CollisionComponent>(pObject);
		if (pObjectCollisionComponent == NULL)
			return;

		CollisionBinMapIterator result = m_collisionBins.find(execId);
		if (result != m_collisionBins.end())
		{
			
			CollisionBin* collisionBin = result->second;
			assert(collisionBin);

			std::vector<GameObject*>* objList = collisionBin->GetCurrentObjectList();
			std::vector<GameObject*>::iterator objIt;
			for (objIt = objList->begin(); objIt != objList->end(); objIt++)
			{
				GameObject* pObjDest = *objIt;
				CollisionComponent* pObjDestCollisonComponent = component_cast<CollisionComponent>(pObjDest);
				if (pObjDest == pObject || pObjDestCollisonComponent == NULL)
				{
					continue;
				}

				if (pObjectCollisionComponent->Intersects(*pObjDestCollisonComponent))
				{
					CollisionEventData collisionObjectData;
					collisionObjectData.m_pCollider = pObjDest;

					SendComponentEventToHandler(Events::COM_COLLISION_EVENT, pObject, *static_cast<EventHandler*>(pObjectCollisionComponent), &collisionObjectData);

				}
			}
			
		}
	}

	void CollisionManager::TestAgainstBin(GameObject* pObject)
	{
		TestAgainstBin(GetActiveExecutor(), pObject);
	}

	std::vector<GameObject*>* CollisionManager::GetCurrentObjectList()
	{
		

		std::vector<GameObject*>* objectListResult = NULL;
		CollisionBinMapIterator result = m_collisionBins.find(GetActiveExecutor());
		if (result != m_collisionBins.end())
		{
			CollisionBin* collisionBin = result->second;




			RECT viewport = Renderer::GetSingletonPtr()->GetCamera().GetViewPort();
			Rect range = Rect(viewport.left, viewport.top, viewport.right - viewport.left, viewport.bottom - viewport.top);

			//FPSCounter::GetSingletonPtr()->StartCounterTest1();
			collisionBin->QueryRange(range);
			
			//Console::GetSingletonPtr()->print("Query Range Time (%lf)", FPSCounter::GetSingletonPtr()->GetCounterTest1());
			objectListResult = collisionBin->GetCurrentObjectList();
		}
		return objectListResult;
	}

	

	/*void CollisionManager::TestAgainstBin(const unsigned int binIndex, CollisionComponent* pObject)
	{
		assert(binIndex < m_collisionBins.size());
		CollisionBin& bin = m_collisionBins[binIndex];
		CollisionComponent* pBinObject = bin.GetFirst();
		while (pBinObject)
		{
			if (pBinObject != pObject && pBinObject->Intersects(*pObject))
			{
				CollisionEventData collisionData;
				collisionData.m_pCollider = pBinObject->GetOwner();
				//SendEventToHandler(Events::SCE_COLLISION_EVENT, *static_cast<EventHandler*>(pObject), &collisionData);
				SendEventToHandlerComponent(Events::COM_COLLISION_EVENT, pObject->GetOwner()->GetId(), *static_cast<EventHandler*>(pObject), &collisionData);

				CollisionEventData collisionDataTest;
				collisionDataTest.m_pCollider = pObject->GetOwner();
				SendEventToHandlerComponent(Events::COM_COLLISION_EVENT, pBinObject->GetOwner()->GetId(), *static_cast<EventHandler*>(pBinObject), &collisionDataTest);
			}
			pBinObject = bin.GetNext();
		}
	}*/
}