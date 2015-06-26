#include "CollisionManager.h"
#include "../GameObjects/GameObject.h"
#include "../EventManager/EventManager.h"
#include "../Utilities/FPSCounter.h"
#include "../Utilities/Console.h"

namespace Framework
{
	CollisionManager::CollisionManager()
		: m_collisionBins(50)
	{
	}

	CollisionManager::~CollisionManager()
	{
		
	}

	CollisionBin* CollisionManager::_getCollisionBin(ExecutorID execId)
	{
		CollisionBin* collisionBin = NULL;
		try {
			collisionBin = m_collisionBins.at(execId);
		}
		catch (const std::out_of_range& oor) {
			Log::error("Try to register collision bin with id out of range (%d) reson (%s)", execId, oor.what());
			throw new GameError(GameErrorNS::FATAL_ERROR, oor.what());
		}
		return collisionBin;
	}

	void CollisionManager::AddCollisionBinFromTileMap(TileMap* tileMap, EventExecutorAware* exec)
	{
		assert(tileMap);
		SetExecutor(exec);

		Quadtree* qtree = tileMap->GetQuadTree();
		//ObjectHashTable* objTable = tileMap->GetOjectHashTable();
		ObjectVector* objVector = tileMap->GetObjectVector();
		CollisionBin* collBin = new CollisionBin(exec->GetExecutorId(), qtree, objVector);
		AddCollisionBin(exec->GetExecutorId(), collBin);
	}

	void CollisionManager::AddCollisionBin(ExecutorID execId, CollisionBin* collisionlBin)
	{
		CollisionBin* collisionBin = _getCollisionBin(execId);
		if (collisionBin == NULL)
		{
			m_collisionBins[execId] = collisionlBin;
		}
		else
		{
			Log::error("Try to assign new collision Bin, but not un allocate old collision bin!");
		}
	}

	void CollisionManager::TestObjectAgainstBin(ExecutorID execId, GameObject* pObject)
	{
		CollisionComponent* pObjectCollisionComponent = component_cast<CollisionComponent>(pObject);
		if (pObjectCollisionComponent == NULL)
			return;

		std::vector<GameObject*>* objList = m_collisionBins[execId]->GetCurrentObjectList();
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
				collisionObjectData.m_pSource = pObject;

				SendComponentEventToHandler(Events::COM_COLLISION_EVENT, pObject, *static_cast<EventHandler*>(pObjectCollisionComponent), &collisionObjectData);

			}
		}//end for
	}

	void CollisionManager::TestObjectsAgainstBin(ExecutorID execId, std::vector<GameObject*>* pObjects)
	{
		std::vector<GameObject*>* objList = m_collisionBins[execId]->GetCurrentObjectList();
		std::vector<GameObject*>::iterator objTestIt, objCollisionIt;
		GameObject* pObject = NULL, * pObjectTest = NULL;
		CollisionComponent* pObjectCollisionComponent = NULL, * pObjDestCollisonComponent = NULL;

		for (objCollisionIt = pObjects->begin(); objCollisionIt != pObjects->end(); objCollisionIt++)
		{
			pObject = *objCollisionIt;
			pObjectCollisionComponent = component_cast<CollisionComponent>(pObject);
			if (pObjectCollisionComponent == NULL || !pObjectCollisionComponent->IsActive())
			{
				FPSCounter::GetSingletonPtr()->IncreaseLoopCounter(1);
				continue;
			}
			for (objTestIt = objList->begin(); objTestIt != objList->end(); objTestIt++)
			{
				pObjectTest = *objTestIt;
				pObjDestCollisonComponent = component_cast<CollisionComponent>(pObjectTest);
				if (pObjDestCollisonComponent == pObjectCollisionComponent)
				{
					continue;
				}

				FPSCounter::GetSingletonPtr()->IncreaseLoopCounter(2);

				if (pObjectCollisionComponent->Intersects(*pObjDestCollisonComponent))
				{

					CollisionEventData collisionObjectData;
					collisionObjectData.m_pCollider = pObjectTest;
					collisionObjectData.m_pSource = pObject;

					SendComponentEventToHandler(Events::COM_COLLISION_EVENT, pObject, *static_cast<EventHandler*>(pObjectCollisionComponent), &collisionObjectData);
				}
			}//end for inner

		}//end for
	}
}