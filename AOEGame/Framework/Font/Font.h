#ifndef __FONT_H__
#define __FONT_H__

#include "../Renderer/Drawable.h"
#include "../Renderer/Texture/Texture.h"

namespace Framework
{
	class Font
		:	public Drawable
	{
	private:
		Texture* m_fontTexture;

	public:
		Font();

		virtual void Draw(LPD3DXSPRITE spriteHandler);
	};
}

#endif