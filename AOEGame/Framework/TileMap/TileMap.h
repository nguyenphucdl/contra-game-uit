#ifndef __TILEMAP_H__
#define __TILEMAP_H__
#include "../Application/Context.h"
#include "TileSet.h"
#include "../GameObjects/GameObject.h"
#include "../Quadtree/Quadtree.h"
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
		string					m_tag;
		int						m_tileWidth;
		int						m_tileHeight;
		int						m_width;
		int						m_height;
		vector<int>*			m_mapData; 		
		vector<TileSet*>*		m_tileSets;
		unordered_map<int, GameObject*>* m_objectHashTable;
		Quadtree*				m_quadtree;
		RECT					m_bound;

		//RENDER TO SURFACE
		LPDIRECT3DSURFACE9		m_tileMapSurface;
		LPDIRECT3DTEXTURE9		m_tileMapTexture;

	private:
		void	_renderToSurface();
	public:
		int		GetTileWidth() { return m_tileWidth; }
		int		GetTileHeight() { return m_tileHeight; }
		RECT	GetBound() { return m_bound; }
		int		GetWidth() { return m_width; }
		int		GetHeight() { return m_height; }
		void    SetMapData(vector<int>* data);
		std::string  GetTag()
		{
			return m_tag;
		}
		void	SetTag(std::string name)
		{
			m_tag = name;
		}
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
		void SetObjects(unordered_map<int, GameObject*>* objHashTable)
		{
			m_objectHashTable = objHashTable;
		}


		unordered_map<int, GameObject*>* GetOjectHashTable()
		{
			return m_objectHashTable;
		}

		void SetQuadTree(Quadtree* quadtree)
		{
			m_quadtree = quadtree;
		}

		Quadtree* GetQuadTree()
		{
			return m_quadtree;
		}
		bool	Init();
	};
}
#endif