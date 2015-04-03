#ifndef __TEXT_H__
#define __TEXT_H__
#include <string>

namespace Framework
{
	class TextDraw
	{
		friend class Font;
	private:
		int m_x, m_y;
		int m_color;
		std::string m_text;

	public:
		TextDraw(int x, int y, std::string text, int color) {
			this->m_x = x;
			this->m_y = y;
			this->m_text = text;
			this->m_color = color;
		}
		TextDraw() : m_x(0), m_y(0), m_color(0xFFFFFFFF), m_text("") {}
			
		virtual ~TextDraw(void) { }

		int getX()					{ return m_x; }
		int getY()					{ return m_y; }
		int getColor()				{ return m_color; }
		std::string	getText()		{ return m_text; }

		void setX(int x)			{ m_x = x; }
		void setY(int y)			{ m_y = y; }
		void setColor(int color)	{ m_color = color; }
		void setText(std::string text)   { m_text = text; }

		
	};
}

#endif