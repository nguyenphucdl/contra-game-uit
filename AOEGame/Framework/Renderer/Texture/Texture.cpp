#include "Texture.h"

namespace Framework
{
	Texture::Texture(std::string name, TEXTURE texture, TEXTUREINFO info)
		: m_name(name)
		, m_texture(texture)
		, m_info(info)
	{
	}

	Texture::~Texture()
	{
	}
	
	void Texture::Destroy()
	{
		SAFE_RELEASE(m_texture);
	}
}
