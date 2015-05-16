#ifndef __TEXTURE_REGION__
#define __TEXTURE_REGION__

#include "Texture.h"
#include <math.h>

namespace Framework
{
	class TextureRegion
	{
	private:
		Texture*	m_texture;
		RECT		m_rect;
		bool		m_flipX;
	public:
		explicit TextureRegion(Texture* texture, RECT rect);
		explicit TextureRegion(Texture* texture, int rtop, int rleft, int rwidth, int rheight);	
		~TextureRegion();

		Texture*	GetTexture() { return m_texture; }
		RECT&		GetRect()	 { return m_rect;	 }
		int			GetTextureWidth() { return abs(m_rect.right - m_rect.left); }
		int			GetTextureHeight() { return abs(m_rect.bottom - m_rect.top); }
		bool		GetFlipX()	{ return m_flipX; }
		void		SetFlipX(bool flipx) { m_flipX = flipx; }
	};
}
#endif//__TEXTURE_REGION__