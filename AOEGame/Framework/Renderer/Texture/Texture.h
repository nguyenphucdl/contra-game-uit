#ifndef __TEXTURE_H__
#define	__TEXTURE_H__
// Texture of Texture Atlas
#include "../../Application/Context.h"

namespace Framework
{
	class Texture
	{
	public:
		typedef LPDIRECT3DTEXTURE9	TEXTURE;
		typedef D3DXIMAGE_INFO		TEXTUREINFO;
	private:
		std::string			m_name;
		TEXTURE				m_texture;
		TEXTUREINFO			m_info;
		int					m_width;
		int					m_height;

	public:
		explicit Texture(std::string name, TEXTURE texture, TEXTUREINFO info);
		explicit Texture(std::string name, TEXTURE texture, int width, int height);
		virtual ~Texture();
		void	 Destroy();

		std::string		GetName()		{ return m_name;			}
		UINT			GetWidth()		{ return m_width;			}
		UINT			GetHeight()		{ return m_height;			}
		TEXTURE			GetTexture()	{ return m_texture;			}
	};
}


#endif//__TEXTURE_H__