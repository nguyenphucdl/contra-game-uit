#include "CollisionBin.h"

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

		////test
		//int i = 0;
		//for (ObjectHashTableIterator it = m_objectHashTable->begin(); it != m_objectHashTable->end(); it++)
		//{
		//	i++;
		//	if (i > 20)
		//		break;
		//	m_currentObjects->push_back(it->second);
		//}
		//return;

		assert(m_collisionObjects);

		m_collisionObjects->QueryRangeUniqueResult(range, matchObjId);

		m_currentObjects->clear();
		std::vector<int>::iterator it;
		int objId;
		for (it = matchObjId->begin(); it != matchObjId->end(); it++)
		{
			objId = *it;
			ObjectHashTableIterator findIt =  m_objectHashTable->find(objId);
			if (findIt != m_objectHashTable->end())
			{
				GameObject* obj = findIt->second;
				m_currentObjects->push_back(obj);
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