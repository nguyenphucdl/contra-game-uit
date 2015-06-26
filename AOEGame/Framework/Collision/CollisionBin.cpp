#include "CollisionBin.h"
#include "../Utilities/Enums.h"
#include "../GameObjects/Components/RangeOfMovementComponent.h"
#include "../GameObjects/Components/BulletComponent.h"

namespace Framework
{
	CollisionBin::CollisionBin(ExecutorID execId, CollisionComponentQuadtree* qt, ObjectHashTable* obj)
		: m_execId(execId)
		, m_collisionObjects(qt)
		, m_objectHashTable(obj)
		, m_currentViewport(-1, -1, -1, -1)
		, m_updateObjects(20)
		, m_currentObjects(100)
		, m_matchQueryDataSet()
	{
		m_updateObjects.clear();
		m_currentObjects.clear();
		m_matchQueryDataSet.clear();
	}

	CollisionBin::~CollisionBin()
	{
		
	}

	void CollisionBin::QueryRange(Rect& range)
	{
		m_matchQueryDataSet.clear();
		m_currentObjects.clear();

		m_collisionObjects->QueryRangeUniqueResult(range);
		const std::vector<int>* matchIdList = m_collisionObjects->GetDataSet();

		std::vector<int>::const_iterator matchIdIt, objInRangeIt;
		ObjectHashTableIterator objectInHashTableIt;
		int objId = -1, objTargetId = -1;
		GameObject *obj = NULL, *objTarget = NULL;
		RangeOfMovementComponent* pRomComponent = NULL;

		for (matchIdIt = matchIdList->begin(); matchIdIt != matchIdList->end(); matchIdIt++)
		{
			m_dataSetIter = m_matchQueryDataSet.insert(*matchIdIt);
			if (m_dataSetIter.second)//newly add id
			{
				objectInHashTableIt = m_objectHashTable->find(*matchIdIt);
				if (objectInHashTableIt != m_objectHashTable->end())
				{
					obj = objectInHashTableIt->second;
					if (obj->GetType() == ObjectTypes::RANGE_OF_MOMENT)
					{
						//Insert data in range of movement
						pRomComponent = component_cast<RangeOfMovementComponent>(obj);
						if (pRomComponent)
						{
							const std::vector<int>* pObjectsInRange = pRomComponent->GetObjectsInRange();
							for (objInRangeIt = pObjectsInRange->begin(); objInRangeIt != pObjectsInRange->end(); objInRangeIt++)
							{
								m_dataSetIter = m_matchQueryDataSet.insert(*objInRangeIt);
								if (m_dataSetIter.second)//newly add id
								{
									objectInHashTableIt = m_objectHashTable->find(*objInRangeIt);
									if (objectInHashTableIt != m_objectHashTable->end())
									{
										objTarget = objectInHashTableIt->second;
										m_currentObjects.push_back(objTarget);
										if (objTarget->GetType() == ObjectTypes::SPAWNLOCATION)
										{
											BulletComponent* pBulletComponent = component_cast<BulletComponent>(objTarget);
											if (pBulletComponent)
											{
												std::vector<GameObject*> *bullets = pBulletComponent->GetBullets();
												m_currentObjects.insert(m_currentObjects.end(), bullets->begin(), bullets->end());
											}
										}

									}
								}
							}
						}//end range of movement
					}
					else
					{
						m_currentObjects.push_back(obj);
					}
				}
			}//end if data set return true
		}//end for match id list
		m_currentObjects.insert(m_currentObjects.end(), m_updateObjects.begin(), m_updateObjects.end());
		m_currentViewport = range;
	}
}