#ifndef __FONT_H__
#define __FONT_H__

#include "../Renderer/Drawable.h"
#include "../Renderer/Texture/Texture.h"
#include "TextDraw.h"
#include "../EventManager/EventHandler.h"

namespace Framework
{
	class Font
		: public Drawable
		, public EventHandler
	{
	private:
		typedef std::vector<TextDraw*>		TextDrawVector;
		typedef	TextDrawVector::iterator	TextDrawVectorIterator;

		Texture*				m_fontTexture;
		TextDrawVector			m_textDraws;

		int m_width, m_height, m_columns;
		int widths[256];

		
		void DrawText(TextDraw* textdraw, LPD3DXSPRITE spriteHandler);
	public:
		Font();
		virtual ~Font() { }



		void Print(int x, int y, std::string text, int color = 0xFFFFFFFF);
		virtual void Draw(LPD3DXSPRITE spriteHandler);

		int getCharWidth() { return this->m_width; }
		int getCharHeight() { return this->m_height; }
		int getColumns() { return m_columns; }

		void setCharWidth(int width) { this->m_width = width; }
		void setColumns(int columns) { this->m_columns = columns; }
		void setCharSize(int width, int height) {
			setCharWidth(width);
			this->m_height = height;
		}

		bool loadWidthData(std::string filename);

		void HandleEvent(Event* pEvent);
	};
}

#endif