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
		: public Singleton<Console>
		, public Drawable
		, public EventHandler

	{
	private:
		bool				m_showing;
		Texture*			m_panel;
		Font*				m_font;
		int					m_currentLine;
		float				m_scaleX, m_scaleY;

		int					m_lineHeight;
		int					m_lineWidthLimit;
	private:
		virtual void Draw(LPD3DXSPRITE spriteHandler);
	public:
		Console();
		virtual ~Console();
		bool init();
		void print(const char* pMessage, ...);
		bool isShowing() { return this->m_showing; }
		void show()		 { this->m_showing = true; }
		void hide()		 { this->m_showing = false; }

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif

/* End of file*/
