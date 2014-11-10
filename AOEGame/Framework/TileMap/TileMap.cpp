#include "TileMap.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/Texture/TextureManager.h"
namespace Framework
{
	TileMap::TileMap(int tileWidth, int tileHeight, int width, int height)
	{
		m_tileWidth = tileWidth;
		m_tileHeight = tileHeight;
		m_width = width;
		m_height = height;
		m_version = "1.0";
	}

	TileMap::~TileMap()
	{
		m_mapData->clear();
		delete m_mapData;
	}

	void TileMap::SetMapData(vector<int>* data)
	{
		m_mapData = data;
	}

	bool TileMap::Init()
	{
		_renderToSurface();
		return true;
	}

	void TileMap::_renderToSurface()
	{
		int mapWidth = m_width * m_tileWidth;
		int mapHeight = m_height * m_tileHeight;

		
		TileSet* tileSet = m_tileSets->at(0);

		Texture* tileSetTexture = GetTexture(tileSet->GetImageName());

		LPDIRECT3DTEXTURE9 lpTileSetTexture = tileSetTexture->GetTexture();

		LPDIRECT3DDEVICE9 device3D = Renderer::GetSingletonPtr()->getD3device();

		LPDIRECT3DSURFACE9 source, origTarget_; 
		tileSetTexture->GetTexture()->GetSurfaceLevel(0, &source);
		// store orginal rendertarget
		device3D->GetRenderTarget( 0, &origTarget_ );
		D3DSURFACE_DESC desc;
		origTarget_->GetDesc( &desc );
		
		// create our surface as render target
		device3D->CreateRenderTarget( mapWidth, mapHeight, desc.Format, 
                                  desc.MultiSampleType, desc.MultiSampleQuality,
                                  false, &m_tileMapSurface, NULL );
		RECT srcDraw, destDraw;


		RECT srcSource, srcDest;
		for(int m = 0; m < m_height; m++)
		{
			for(int n = 0; n < m_width; n++)
			{
				int drawGid = m_mapData->at(m * m_width + n);
				int tileSetId = drawGid - tileSet->GetFirstGid();

				srcDraw.left = ((tileSetId % tileSet->GetDimensionX()) * m_tileWidth );
				srcDraw.right = srcDraw.left + m_tileWidth;
				srcDraw.top = (( tileSetId / tileSet->GetDimensionX()) * m_tileHeight);
				srcDraw.bottom = srcDraw.top + m_tileHeight;

				srcDest.left = n * m_tileWidth;
				srcDest.right = srcDest.left + m_tileWidth;
				srcDest.top = m * m_tileHeight;
				srcDest.bottom = srcDest.top + m_tileHeight;

				device3D->StretchRect(source, &srcDraw, m_tileMapSurface, &srcDest, D3DTEXTUREFILTERTYPE::D3DTEXF_NONE);
			}
			
		}


		
		

		D3DXSaveSurfaceToFile("test123Surface.png", D3DXIMAGE_FILEFORMAT::D3DXIFF_PNG, m_tileMapSurface, NULL, NULL);
	}
}