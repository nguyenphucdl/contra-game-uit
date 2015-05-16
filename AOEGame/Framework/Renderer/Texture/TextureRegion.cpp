#include "TextureRegion.h"

namespace Framework
{
	TextureRegion::TextureRegion(Texture* texture, RECT rect)
		: m_texture(texture)
		, m_rect(rect)
		, m_flipX(false)
	{
	}

	TextureRegion::TextureRegion(Texture* texture, int rleft, int rtop, int rwidth, int rheight)
	{
		m_texture = texture;
		m_rect.left = rleft;
		m_rect.right = rleft + rwidth;
		m_rect.top = rtop;
		m_rect.bottom = rtop + rheight;
	}

	TextureRegion::~TextureRegion()
	{
		SAFE_DELETE(m_texture);
	}
}