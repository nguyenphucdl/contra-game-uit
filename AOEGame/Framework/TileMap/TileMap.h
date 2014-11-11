#ifndef __TILEMAP_H__
#define __TILEMAP_H__
#include "../Application/Context.h"
#include "TileSet.h"
using  namespace std;

namespace Framework
{
	class TileMap
	{
	public:
		TileMap(int tileWidth, int tileHeight, int width, int height);
		~TileMap();

	private:
		string					m_version;
		int						m_tileWidth;
		int						m_tileHeight;
		int						m_width;
		int						m_height;
		vector<int>*			m_mapData; 		
		vector<TileSet*>*		m_tileSets;

		//RENDER TO SURFACE
		LPDIRECT3DSURFACE9		m_tileMapSurface;
		LPDIRECT3DTEXTURE9		m_tileMapTexture;

	private:
		void	_renderToSurface();
	public:
		int		GetTileWidth() { return m_tileWidth; }
		int		GetTileHeight() { return m_tileHeight; }
		int		GetWidth() { return m_width; }
		int		GetHeight() { return m_height; }
		void    SetMapData(vector<int>* data);
		LPDIRECT3DSURFACE9	GetSurface()
		{
			return m_tileMapSurface;
		}
		void	SetTileSets(vector<TileSet*>* tileSets)
		{
			m_tileSets = tileSets;
		}
		vector<TileSet*>*	GetTileSets()
		{
			return m_tileSets;
		}
		bool	Init();
	};
}
#endif