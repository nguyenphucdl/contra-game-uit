#ifndef __COLLISION_H__
#define __COLLISION_H__

#include <vector>
#include "../Quadtree/Quadtree.h"
#include "../GameObjects/Components/CollisionComponent.h"
#include "../EventManager/EventExecutorAware.h"
#include "../GameObjects/Components/BulletComponent.h"

namespace Framework
{
	typedef Quadtree										CollisionComponentQuadtree;
	typedef std::tr1::unordered_map<ObjectId, GameObject*>	ObjectHashTable;
	typedef ObjectHashTable::iterator						ObjectHashTableIterator;
	
	class CollisionBin
	{
	private:
		
		CollisionComponentQuadtree*			m_collisionObjects;
		ObjectHashTable*					m_objectHashTable;
		ExecutorID							m_execId;

		
			
		std::vector<GameObject*>::iterator			m_objectIter;

		std::vector<GameObject*>					m_currentObjects;
		std::vector<GameObject*>					m_updateObjects;
		std::set<int>								m_matchQueryDataSet;
		std::pair<std::set<int>::iterator, bool>	m_dataSetIter;

		Rect										m_currentViewport;

	public:
		CollisionBin(ExecutorID execId, CollisionComponentQuadtree* qt, ObjectHashTable* obj);
		~CollisionBin();

		void QueryRange(Rect& range);

		void AddUpdateObject(GameObject* pObj);
		void AddUpdateObjects(std::vector<GameObject*>* objects);
		void Init();


		std::vector<GameObject*>* GetCurrentObjectList()	{ return &m_currentObjects; }
	};

	inline void CollisionBin::AddUpdateObject(GameObject* pObj)
	{
		m_updateObjects.push_back(pObj);
		BulletComponent* pBulletComponent = component_cast<BulletComponent>(pObj);
		if (pBulletComponent != NULL)
		{
			std::vector<GameObject*>* bullets = pBulletComponent->GetBullets();
			assert(bullets);
			if (bullets)
			{
				m_updateObjects.insert(m_updateObjects.begin(), bullets->begin(), bullets->end());
			}
		}
	}

	inline void CollisionBin::AddUpdateObjects(std::vector<GameObject*>* objects)
	{
		BulletComponent* pBulletComponent = NULL;
		std::vector<GameObject*>* bullets = NULL;
		for (std::vector<GameObject*>::iterator it = objects->begin(); it != objects->end(); it++)
		{
			AddUpdateObject(*it);
		}
	}

	inline void CollisionBin::Init()
	{
		for (m_objectIter = m_updateObjects.begin(); m_objectIter != m_updateObjects.end(); m_objectIter++)
		{
			GameObject* obj = *m_objectIter;
			if (obj)
				obj->InitializeComponents();
		}
	}
}
#endif