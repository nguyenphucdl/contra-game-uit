#include "Quadtree.h"
#include "../Log/Log.h"
#include "../Utilities/Console.h"
#include "../Utilities/FPSCounter.h"

namespace Framework
{
	Quadtree::Quadtree(int level, Rect& bound)
		: m_level(level)
		, m_bound(bound)
		, m_id(-1)
		, m_parent(NULL)
		, NE(NULL), NW(NULL), SW(NULL), SE(NULL)
		, m_listObjectId(NULL)
	{
	}



	Quadtree::~Quadtree()
	{
	}

	void Quadtree::Clear()
	{
		m_listObjectId->clear();	SAFE_DELETE(m_listObjectId);
		SAFE_DELETE(m_parent);
		NE->Clear();	SAFE_DELETE(NE);
		NW->Clear();	SAFE_DELETE(NW);
		SW->Clear();	SAFE_DELETE(SW);
		SE->Clear();	SAFE_DELETE(SE);
	}

	bool Quadtree::IsExternal()
	{
		if (NE != NULL)
			return false;
		return true;
	}

	void Quadtree::Quadrant()
	{
		int subWidth = m_bound.GetWidth() / 2;
		int subHeight = m_bound.GetHeight() / 2;

		Rect neBound = Rect(m_bound.GetX(), m_bound.GetY(), subWidth, subHeight);
		Rect nwBound = Rect(m_bound.GetX() + subWidth, m_bound.GetY(), subWidth, subHeight);
		Rect swBound = Rect(m_bound.GetX() + subWidth, m_bound.GetY() + subHeight, subWidth, subHeight);
		Rect seBound = Rect(m_bound.GetX(), m_bound.GetY() + subHeight, subWidth, subHeight);

		NE = new Quadtree(m_level + 1, neBound);
		NE->m_parent = this;
		NW = new Quadtree(m_level + 1, nwBound);
		NW->m_parent = this;
		SW = new Quadtree(m_level + 1, swBound);
		SW->m_parent = this;
		SE = new Quadtree(m_level + 1, seBound);
		SE->m_parent = this;
	}

	void Quadtree::InsertData(int objId)
	{
		if (m_listObjectId == NULL)
			m_listObjectId = new std::vector<int>();

		m_listObjectId->push_back(objId);
	}

	Quadtree* Quadtree::InitNodeData(int id, int parentId, int level, std::vector<int>* data)
	{
		Quadtree* parentNode = GetRelativeById(parentId);
		Quadtree* resultInitNode = NULL;
		if (parentNode == NULL)
		{
			Log::error("Init node failed with id(%d) parentId(%d) level(%d)", id, parentId, level);
			return resultInitNode;
		}
		if (parentNode!= NULL)
		{
			if (level == 0)
			{
				resultInitNode = parentNode;
			}
			else
			{
				if (parentNode->IsExternal())
				{
					parentNode->Quadrant();
				}
				resultInitNode = parentNode->GetInvalidChild();
			}
			if (resultInitNode != NULL)
			{
				resultInitNode->m_id = id;
				resultInitNode->m_level = level;
				resultInitNode->m_listObjectId = data;
			}
			else
			{
				Log::error("Get child node failed with id(%d) parentId(%d) level(%d)", id, parentId, level);
			}
		}
		return resultInitNode;
	}

	Quadtree* Quadtree::GetRelativeById(int id)
	{
		Quadtree* relative = this;
		while (true)
		{
			if (relative == NULL)
			{
				return NULL;
			}
			if (relative->m_id == id)
			{
				return relative;
			}
			relative = relative->GetParent();
		}
		return NULL;
	}

	Quadtree* Quadtree::FindNodeById(int id)
	{
		Quadtree* result = NULL;
		if (this->m_id == id)
			return this;
		if (NE == NULL)
			return NULL;
		result = NE->FindNodeById(id);
		if (result != NULL)
			return result;
		result = NW->FindNodeById(id);
		if (result != NULL)
			return result;
		result = SE->FindNodeById(id);
		if (result != NULL)
			return result;
		result = SW->FindNodeById(id);
		if (result != NULL)
			return result;
		return result;
	}

	Quadtree* Quadtree::GetInvalidChild()
	{
		if (NE == NULL)
			return NULL;
		if (NE->m_id == -1)
			return NE;
		if (NW->m_id == -1)
			return NW;
		if (SE->m_id == -1)
			return SE;
		if (SW->m_id == -1)
			return SW;
		return NULL;
	}

	void Quadtree::QueryRangeUniqueResult(Rect& rect, std::vector<int>* returnObjIdList)
	{
		//FPSCounter::GetSingletonPtr()->StartCounterTest1();
		if (true)
		{
			QueryRange(rect, returnObjIdList);
			std::sort(returnObjIdList->begin(), returnObjIdList->end());
			std::vector<int>::iterator it = std::unique(returnObjIdList->begin(), returnObjIdList->end());
			returnObjIdList->resize(std::distance(returnObjIdList->begin(), it));
		}

		//Console::GetSingletonPtr()->print("Query Range Time (%lf)", FPSCounter::GetSingletonPtr()->GetCounterTest1());
	}

	void Quadtree::QueryRange(Rect& range, std::vector<int>* returnObjIdList)
	{
		if (!m_bound.IsIntersect(range))
			return;
		if (this->IsExternal())
		{
			if (m_listObjectId == NULL)
				return;
			std::vector<int>::iterator it;
			for (it = m_listObjectId->begin(); it != m_listObjectId->end() ; it++)
			{
				returnObjIdList->push_back(*it);
			}
		}
		else
		{
			NE->QueryRange(range, returnObjIdList);
			NW->QueryRange(range, returnObjIdList);
			SW->QueryRange(range, returnObjIdList);
			SE->QueryRange(range, returnObjIdList);
		}
	}
}