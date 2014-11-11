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
		//RECT srcDraw, destDraw;

		RECT srcSource, srcDest;
		for(int m = 0; m < m_height; m++)
		{
			for(int n = 0; n < m_width; n++)
			{
				int drawGid = m_mapData->at(m * m_width + n);
				int tileSetId = drawGid - tileSet->GetFirstGid();

				srcSource.left = ((tileSetId % tileSet->GetDimensionX()) * m_tileWidth);
				srcSource.right = srcSource.left + m_tileWidth;
				srcSource.top = ((tileSetId / tileSet->GetDimensionX()) * m_tileHeight);
				srcSource.bottom = srcSource.top + m_tileHeight;

				srcDest.left = n * m_tileWidth;
				srcDest.right = srcDest.left + m_tileWidth;
				srcDest.top = m * m_tileHeight;
				srcDest.bottom = srcDest.top + m_tileHeight;

				device3D->StretchRect(source, &srcSource, m_tileMapSurface, &srcDest, D3DTEXTUREFILTERTYPE::D3DTEXF_NONE);
			}
			
		}

		D3DXSaveSurfaceToFile("test123Surface.png", D3DXIMAGE_FILEFORMAT::D3DXIFF_PNG, m_tileMapSurface, NULL, NULL);
		
		LPDIRECT3DSURFACE9 pSurface;

		HRESULT result1 = device3D->CreateOffscreenPlainSurface(
			mapWidth,
			mapHeight,
			D3DFMT_X8R8G8B8,
			D3DPOOL_SYSTEMMEM,
			&pSurface,
			NULL);
		if (FAILED(result1))
		{
			throw new GameError(GameErrorNS::FATAL_ERROR, "Cannot create tilemap surface!");
		}

		result1 = device3D->GetRenderTargetData(m_tileMapSurface, pSurface);
		if (FAILED(result1))
		{
			throw new GameError(GameErrorNS::FATAL_ERROR, "Cannot get render target data!");
		}


		HRESULT result = D3DXCreateTexture(
			device3D,
			mapWidth,
			mapHeight,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_X8R8G8B8,
			D3DPOOL_DEFAULT,
			&m_tileMapTexture);

		if (FAILED(result))
		{
			throw new GameError(GameErrorNS::FATAL_ERROR, "Cannot create tilemap texture!");
		}
		IDirect3DSurface9 *pTextureSurface;
		if (SUCCEEDED(m_tileMapTexture->GetSurfaceLevel(0, &pTextureSurface)))
		{
			result = device3D->UpdateSurface(pSurface, NULL, pTextureSurface, NULL);
			if (FAILED(result))
			{
				throw new GameError(GameErrorNS::FATAL_ERROR, "Cannot copy surface to tilemap texture!");
			}
			pTextureSurface->Release();
			pSurface->Release();
		}
		
		D3DXSaveTextureToFile("test123Texture.png", D3DXIMAGE_FILEFORMAT::D3DXIFF_PNG, m_tileMapTexture, NULL);
	}
}