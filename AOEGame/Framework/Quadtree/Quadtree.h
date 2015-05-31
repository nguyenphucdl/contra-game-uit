#ifndef __QUADTREE_H__
#define	__QUADTREE_H__

#include "../Application/Context.h"

#define MAXOBJECTS 5
#define MAXLEVEL 5

namespace Framework
{
	class Quadtree
	{
	private:
		int			m_id;
		int			m_level;
		Rect		m_bound;
		Quadtree*	m_parent;

		std::vector<int>* m_listObjectId;

		Quadtree*	NE;
		Quadtree*	NW;
		Quadtree*	SW;
		Quadtree*	SE;
		


	public:
		Quadtree(int level, Rect& bound);
		~Quadtree();

		void	Clear();
		bool	IsExternal();
		void	Quadrant();
		void	InsertData(int objId);
	
		Quadtree* InitNodeData(int id, int parentId, int  level, std::vector<int>* data);
	
		Quadtree* GetInvalidChild();
		Quadtree* FindNodeById(int id);
		Quadtree* FindParentById(int id);
		Quadtree* GetRelativeById(int id);
		Quadtree* GetParent()  { return m_parent; };
		
	public:
		void QueryRange(Rect& range, std::vector<int>* returnObjIdList);
	};
}

#endif