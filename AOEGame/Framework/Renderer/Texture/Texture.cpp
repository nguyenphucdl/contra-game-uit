#include "Texture.h"

namespace Framework
{
	Texture::Texture(std::string name, TEXTURE texture, TEXTUREINFO info)
		: m_name(name)
		, m_texture(texture)
		, m_info(info)
		, m_width(info.Width)
		, m_height(info.Height)
	{
	}

	Texture::Texture(std::string name, TEXTURE texture, int width, int height)
		: m_name(name)
		, m_texture(texture)
		, m_width(width)
		, m_height(height)
		, m_info()
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
