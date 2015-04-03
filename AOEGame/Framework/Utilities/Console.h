#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "../Application/Context.h"
#include "../Renderer/Texture/Texture.h"
#include "../../Framework/EventManager/Event.h"
#include "../../Framework/EventManager/EventHandler.h"
#include "../../Framework/EventManager/EventManager.h"
#include "../Font/Font.h"

namespace Framework
{
	class Console 
		: public Drawable
		, public EventHandler

	{
		typedef std::vector<std::string> StringVector;
		typedef StringVector::iterator	 StringVectorIterator;
	private:
		bool				m_showing;
		Texture*			m_panel;
		Font*				m_font;
		int					m_currentLine;
		float				m_scaleX, m_scaleY;
		StringVector		m_textLines;

		int					m_lineHeight;
		int					m_lineWidthLimit;
	private:
		virtual void Draw(LPD3DXSPRITE spriteHandler);
	public:
		Console();
		virtual ~Console() {};
		bool init();
		void print(std::string text, int line = -1);
		bool isShowing() { return this->m_showing; }
		void show()		 { this->m_showing = true; }
		void hide()		 { this->m_showing = false; }

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif

/* End of file*/
