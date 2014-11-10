#ifndef __TILESET_H__
#define __TILESET_H__

#include <string>

namespace Framework
{
	class TileSet
	{
	public:
		TileSet(int firstGid, int tileWidth,
			int tileHeight, std::string imageName, int m_dimensionX, int m_dimensionY ,std::string name);
		~TileSet();
	private:
		int				m_firstGid;
		int				m_tileWidth;
		int				m_tileHeight;
		int				m_dimensionX;
		int				m_dimensionY;
		std::string		m_imageName;
		std::string		m_name;
		

	public:
		int				GetFirstGid() { return m_firstGid; }
		int				GetTileWidth() { return m_tileWidth;}
		int				GetTileHeight() { return m_tileHeight; }
		int				GetDimensionX() { return m_dimensionX; }
		int				GetDimensionY() { return m_dimensionY; }
		std::string		GetImageName() { return m_imageName; }
		std::string		GetName() { return m_name; }
	};
}
#endif