#include "Font.h"
#include "../Renderer/Texture/TextureManager.h"
#include "../EventManager/EventManager.h"

namespace Framework
{
	Font::Font()
		: m_width(0), m_height(0), m_columns(0)
	{
		RegisterTexture("Resources\\Font\\system12.tga");
		m_fontTexture = GetTexture("system12.tga");

		loadWidthData("Resources\\Font\\system12.dat");
		
		Framework::AttachEvent(Events::POST_RENDER_EVENT, *this);
	}

	void Font::Draw(LPD3DXSPRITE spriteHandler)
	{
		for (TextDrawVectorIterator iter = m_textDraws.begin(); iter != m_textDraws.end(); ++iter)
		{
			TextDraw* pTextDraw = *iter;
			DrawText(pTextDraw, spriteHandler);
		}
	}

	void Font::DrawText(TextDraw* textdraw, LPD3DXSPRITE spriteHandler)
	{
		float fx = (float)textdraw->getX();
		float fy = (float)textdraw->getY();

		int color = textdraw->getColor();
		std::string text = textdraw->getText();

		//Draw each character of the string
		RECT srcCharacter;
		int frame, px, py;
		for (unsigned int n = 0; n < text.length(); n++)
		{
			frame = (int)text[n];
			px = frame % m_columns * m_width;
			py = frame / m_columns * m_height;
			srcCharacter = { px, py, px + m_width, py + m_height };
			
			spriteHandler->Draw(m_fontTexture->GetTexture(), &srcCharacter, NULL, &D3DXVECTOR3(fx, fy, 0), color);

			if (widths[frame] == 0) widths[frame] = m_width;
			fx += widths[frame];
		}
	}

	void Font::Print(int x, int y, std::string text, int color)
	{
		TextDraw* t = new TextDraw(x, y, text, color);
		m_textDraws.push_back(t);
	}

	bool Font::loadWidthData(std::string filename)
	{
		unsigned char buffer[512];

		//open font width data file
		std::ifstream infile;
		infile.open(filename.c_str(), std::ios::binary);
		if (!infile) return false;

		//read 512 bytes (2 bytes per character)
		infile.read((char *)(&buffer), 512);
		if (infile.bad()) return false;
		infile.close();

		//convert raw data to proportional width data
		for (int n = 0; n<256; n++) {
			widths[n] = (int)buffer[n * 2];
		}

		return true;
	}

	void Font::HandleEvent(Event* pEvent)
	{
		m_textDraws.clear();
	}
}