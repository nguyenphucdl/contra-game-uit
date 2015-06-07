#ifndef __COLLISION_H__
#define __COLLISION_H__

#include <vector>
#include "../Quadtree/Quadtree.h"
#include "../GameObjects/Components/CollisionComponent.h"
#include "../EventManager/EventExecutorAware.h"

namespace Framework
{
	typedef Quadtree										CollisionComponentQuadtree;
	typedef std::tr1::unordered_map<ObjectId, GameObject*>					ObjectHashTable;
	typedef ObjectHashTable::iterator						ObjectHashTableIterator;
	
	class CollisionBin
	{
	private:
		
		CollisionComponentQuadtree*			m_collisionObjects;
		ObjectHashTable*					m_objectHashTable;
		ExecutorID							m_execId;

		std::vector<GameObject*>*			m_currentObjects;
		Rect								m_currentViewport;

	public:
		CollisionBin(ExecutorID execId, CollisionComponentQuadtree* qt, ObjectHashTable* obj);
		~CollisionBin();

		void QueryRange(Rect& range);
		void QueryRange(Rect& range, std::vector<GameObject*>* returnObjIdList);

		std::vector<GameObject*>* GetCurrentObjectList() { return m_currentObjects; }
	};
}
#endif