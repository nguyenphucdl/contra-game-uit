#include "TileSet.h"

namespace Framework
{
	TileSet::TileSet(int firstGid, int tileWidth,
			int tileHeight, std::string& imageName,int dimensionX, int dimensionY, std::string& name)
			: m_firstGid(firstGid)
			, m_tileWidth(tileWidth)
			, m_tileHeight(tileHeight)
			, m_imageName(imageName)
			, m_dimensionX(dimensionX)
			, m_dimensionY(dimensionY)
			, m_name(name)
	{
	}

	TileSet::~TileSet()
	{
		
	}
}