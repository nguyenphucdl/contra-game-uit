#include "Rect.h"

namespace Framework
{
	Rect::Rect(double x, double y, int width, int height)
		: m_x(x)
		, m_y(y)
		, m_width(width)
		, m_height(height)
	{
	}

	Rect::Rect(Rect& rect)
	{
		m_x = rect.GetX();
		m_y = rect.GetY();
		m_width = rect.GetWidth();
		m_height = rect.GetHeight();
	}

	Rect::~Rect()
	{
	}

	RECT Rect::GetBound()
	{
		RECT result;
		result.left = m_x;
		result.top = m_y;
		result.right = result.left + m_width;
		result.bottom = result.top + m_height;
		return result;
	}
	/*
	* http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
	*/
	bool Rect::IsIntersect(Rect& l, Rect& r)
	{
		bool noOverlap = l.GetX() > r.GetX() + r.GetWidth()
			|| r.GetX() > l.GetX() + l.GetWidth()
			|| l.GetY() > r.GetY() + r.GetHeight()
			|| r.GetY() > l.GetY() + l.GetHeight();
		return !noOverlap;
	}

	bool Rect::IsIntersect(Rect& r)
	{
		return Rect::IsIntersect(*this, r);
	}
}