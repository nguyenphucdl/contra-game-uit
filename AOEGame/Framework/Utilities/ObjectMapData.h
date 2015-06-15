#ifndef __OBJECT_MAP_DATA_H__
#define	__OBJECT_MAP_DATA_H__

#include "../GameObjects/GameObject.h"

namespace Framework
{
	class ObjectMapData
	{
	private:
		int m_x;
		int m_y;
		int m_width;
		int m_height;

	public:
		ObjectMapData();
		ObjectMapData(int x, int y, int w, int h);
		~ObjectMapData() {};

		int GetX()			{ return m_x; }
		int GetY()			{ return m_y; }
		int GetWidth()		{ return m_width; }
		int GetHeight()		{ return m_height; }

		void Set(int x, int y, int w, int h);
	};
	inline ObjectMapData::ObjectMapData()
	{

	}

	inline ObjectMapData::ObjectMapData(int x, int y, int w, int h)
		: m_x(x)
		, m_y(y)
		, m_width(w)
		, m_height(h)
	{
	}

	inline void ObjectMapData::Set(int x, int y, int w, int h)
	{
		m_x = x;
		m_y = y;
		m_width = w;
		m_height = h;
	}
}
#endif