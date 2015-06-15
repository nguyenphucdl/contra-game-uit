#include "CollisionBin.h"
#include "../Utilities/Enums.h"
#include "../GameObjects/Components/RangeOfMovementComponent.h"

namespace Framework
{
	CollisionBin::CollisionBin(ExecutorID execId, CollisionComponentQuadtree* qt, ObjectHashTable* obj)
		: m_execId(execId)
		, m_collisionObjects(qt)
		, m_objectHashTable(obj)
		, m_currentViewport(-1, -1, -1, -1)
	{
		m_currentObjects = new std::vector<GameObject*>();
	}

	CollisionBin::~CollisionBin()
	{
		
	}

	void CollisionBin::QueryRange(Rect& range)
	{
		if (m_currentViewport.GetX() == range.GetX())
			return;
		std::vector<int>* matchObjId = new std::vector<int>(20);

		assert(m_collisionObjects);

		m_collisionObjects->QueryRangeUniqueResult(range, matchObjId);

		m_currentObjects->clear();
		std::vector<int>::iterator it;
		ObjectHashTableIterator findIt;
		int objId = -1, objTargetId = -1;
		GameObject *obj = NULL, *objTarget = NULL;
		RangeOfMovementComponent* pRomComponent = NULL;

		for (it = matchObjId->begin(); it != matchObjId->end(); it++)
		{
			objId = *it;
			findIt =  m_objectHashTable->find(objId);
			if (findIt != m_objectHashTable->end())
			{
				obj = findIt->second; 
				
				if (obj->GetType() == ObjectTypes::RANGE_OF_MOMENT)
				{
					pRomComponent = component_cast<RangeOfMovementComponent>(obj);
					assert(pRomComponent);
					if (pRomComponent)
					{
						objTargetId = pRomComponent->GetObjectTarget();
						findIt = m_objectHashTable->find(objTargetId);
						if (findIt != m_objectHashTable->end())
						{
							objTarget = findIt->second;
							m_currentObjects->push_back(objTarget);
						}
					}

				}
				else
				{
					m_currentObjects->push_back(obj);
				}
			}
		}
		m_currentViewport = range;
	}
	
	void CollisionBin::QueryRange(Rect& range, std::vector<GameObject*>* returnObjIdList)
	{
		QueryRange(range);
		returnObjIdList = m_currentObjects;
	}
}