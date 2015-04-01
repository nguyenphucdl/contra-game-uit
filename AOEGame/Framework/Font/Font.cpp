#include "Font.h"
#include "../Renderer/Texture/TextureManager.h"

namespace Framework
{
	Font::Font()
	{
		RegisterTexture("debug-texture.png");
		m_fontTexture = GetTexture("debug-texture.png");

		Renderer::GetSingletonPtr()->AddDrawable(this);
	}


	void Font::Draw(LPD3DXSPRITE spriteHandler)
	{
		int i = 3;
		spriteHandler->Draw(m_fontTexture->GetTexture(), NULL, NULL, &D3DXVECTOR3(0, 0, 0), D3DCOLOR_XRGB(255, 255, 255));
	}
}