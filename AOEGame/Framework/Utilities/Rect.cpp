#include "Rect.h"

namespace Framework
{
	Rect::Rect()
		: m_x(0)
		, m_y(0)
		, m_width(0)
		, m_height(0)
		, m_rect()
	{

	}

	Rect::Rect(double x, double y, int width, int height)
		: m_x(x)
		, m_y(y)
		, m_width(width)
		, m_height(height)
		, m_rect()
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