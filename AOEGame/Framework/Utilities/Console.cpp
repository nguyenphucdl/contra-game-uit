#include "Console.h"
#include "../Renderer/Renderer.h"

namespace Framework
{
	Console::Console()
		: m_showing(false)
		, m_currentLine(1)
		, m_lineHeight(16)
	{
		Renderer::GetSingletonPtr()->AddDrawable(this);
	}

	Console::~Console()
	{
		SAFE_DELETE(m_panel);
		SAFE_DELETE(m_font);
	}

	bool Console::init()
	{
		m_font = new Font();
		m_font->setCharSize(14, 16);
		m_font->setColumns(16);
		RegisterTexture("Resources\\Font\\panel.png");
		m_panel = GetTexture("panel.png");

		m_lineWidthLimit = Renderer::GetSingletonPtr()->GetWidth() / 2;

		m_scaleX = Renderer::GetSingletonPtr()->GetWidth() / 100.0f;
		m_scaleY = Renderer::GetSingletonPtr()->GetHeight() / (2 * 100.0f);

		Framework::AttachEvent(ExecutorIDs::SysInput, Events::SYS_KEY_DOWN_EVENT, *this);
		Framework::AttachEvent(ExecutorIDs::SysRender, Events::SYS_POST_RENDER_EVENT, *this);
		return true;
	}

	void Console::print(const char* pMessage, ...)
	{
		char buffer[256];
		va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		vsprintf_s(buffer, 256, pMessage, lVarArgs);
		va_end(lVarArgs);
		std::string text(buffer);
		
		int yLine = m_lineHeight * (m_currentLine);
		m_font->Print(0, yLine, text);
		m_currentLine++;
	}
	void Console::Draw(LPD3DXSPRITE spriteHandler)
	{
		if (m_showing == false)
			return;
		D3DXVECTOR2 scaleVector(m_scaleX, m_scaleY);
		D3DXMATRIX  viewMatrix;
		D3DXMatrixIdentity(&viewMatrix);
		D3DXMatrixTransformation2D(&viewMatrix, NULL, 0, &scaleVector, 0, 0, 0);

		D3DXMATRIX backup;
		spriteHandler->GetTransform(&backup);
		spriteHandler->SetTransform(&viewMatrix);
		spriteHandler->Draw(m_panel->GetTexture(), NULL, NULL, &D3DXVECTOR3(0, 0, 0), D3DCOLOR_XRGB(255, 255, 255));

		spriteHandler->SetTransform(&backup);

		m_font->Draw(spriteHandler);
	}

	void Console::HandleEvent(Event* pEvent)
	{
		int keyCode = (int)pEvent->GetData();
		switch (keyCode)
		{
		case DIK_X:
			m_showing = m_showing? false: true;
			break;
		default:
			break;
		}

		if (pEvent->GetID() == Events::SYS_POST_RENDER_EVENT)
		{
			m_currentLine = 0;
		}
	}
}