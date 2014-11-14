#ifndef __TEXTURE_REGION__
#define __TEXTURE_REGION__

#include "Texture.h"

namespace Framework
{
	class TextureRegion
	{
	private:
		Texture*	m_texture;
		RECT		m_rect;
	public:
		explicit TextureRegion(Texture* texture, RECT rect);
		explicit TextureRegion(Texture* texture, int rtop, int rleft, int rwidth, int rheight);	
		~TextureRegion();

		Texture*	GetTexture() { return m_texture; }
		RECT&		GetRect()	 { return m_rect;	 }
	};
}
#endif//__TEXTURE_REGION__