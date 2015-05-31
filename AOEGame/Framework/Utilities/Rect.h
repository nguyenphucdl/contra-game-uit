#ifndef __RECT_H__
#define	__RECT_H__

#include "../Application/Context.h"

namespace Framework
{
	class Rect
	{
	private:
		double	m_x;
		double	m_y;
		int		m_width;
		int		m_height;

	public:
		Rect(double x, double y, int width, int height);
		Rect(Rect& rect);
		~Rect();

		void	SetX(double x)			{ m_x = x; }
		double	GetX()					{ return m_x; }
		void	SetY(double y)			{ m_y = y; }
		double  GetY()					{ return m_y; }
		void	SetWidth(int width)		{ m_width = width; }
		int		GetWidth()				{ return m_width; }
		void	SetHeight(int height)	{ m_width = height; }
		int		GetHeight()				{ return m_height; }

		RECT	GetBound();

		bool	IsIntersect(Rect& r);
		static bool	IsIntersect(Rect& l, Rect& r);
	};
}

#endif