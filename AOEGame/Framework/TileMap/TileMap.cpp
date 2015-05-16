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
		m_tag = "Pre-renderTileMapTexture" + std::to_string(rand() % 100);
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
		LPDIRECT3DDEVICE9 device3D = Renderer::GetSingletonPtr()->getD3device();

		int mapOriginWidth = m_width * m_tileWidth;
		int mapOriginHeight = m_height * m_tileHeight;

		int viewportWidth = Renderer::GetSingletonPtr()->GetWidth();
		int viewportHeight = Renderer::GetSingletonPtr()->GetHeight();


		TileSet* tileSet = m_tileSets->at(0);
		Texture* tileSetTexture = GetTexture(tileSet->GetImageName());
		LPDIRECT3DTEXTURE9 lpTileSetTexture = tileSetTexture->GetTexture();

		LPDIRECT3DSURFACE9 source, backup;
		lpTileSetTexture->GetSurfaceLevel(0, &source);

		// store original rendertarget
		device3D->GetRenderTarget(0, &backup);
		D3DSURFACE_DESC desc;
		backup->GetDesc(&desc);

		//create our surface as render target
		device3D->CreateRenderTarget(mapOriginWidth, mapOriginHeight, desc.Format, 
					desc.MultiSampleType, desc.MultiSampleQuality, false, &m_tileMapSurface, NULL);

		RECT srcSource, srcDest;
		int i = 0;
		for (int m = 0; m < m_height; m++)
		{
			for (int n = 0; n < m_width; n++)
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


				device3D = Renderer::GetSingletonPtr()->getD3device();
				device3D->StretchRect(source, &srcSource, m_tileMapSurface, &srcDest, D3DTEXTUREFILTERTYPE::D3DTEXF_NONE);
			}
		}

		LPDIRECT3DSURFACE9 pViewportSurface;

		float scaleRatio = 1.0f;
		bool isHorizDirection = (mapOriginWidth > mapOriginHeight) ? true : false;
		if (isHorizDirection)
		{
			scaleRatio = (float)viewportHeight / mapOriginHeight;
		}
		else
		{
			scaleRatio = (float)viewportWidth / mapOriginWidth;
		}
			

		int viewportSurfaceWidth = mapOriginWidth * scaleRatio;
		int viewportSurfaceHeight = mapOriginHeight * scaleRatio;
		m_bound.left = 0;
		m_bound.right = viewportSurfaceWidth;
		m_bound.top = 0;
		m_bound.bottom = viewportSurfaceHeight;

		device3D->CreateRenderTarget(viewportSurfaceWidth, viewportSurfaceHeight, desc.Format,
			desc.MultiSampleType, desc.MultiSampleQuality, false, &pViewportSurface, NULL);
		device3D->StretchRect(m_tileMapSurface, NULL, pViewportSurface, NULL, D3DTEXF_NONE);

		//D3DXSaveSurfaceToFile("renderSurfaceOrigin.png", D3DXIMAGE_FILEFORMAT::D3DXIFF_PNG, m_tileMapSurface, NULL, NULL);
		//D3DXSaveSurfaceToFile("renderViewportSurface.png", D3DXIMAGE_FILEFORMAT::D3DXIFF_PNG, pViewportSurface, NULL, NULL);

		LPDIRECT3DSURFACE9 pSurface;
		HRESULT result2 = device3D->CreateOffscreenPlainSurface(
			viewportSurfaceWidth,
			viewportSurfaceHeight,
			D3DFMT_X8R8G8B8,
			D3DPOOL_SYSTEMMEM,
			&pSurface,
			NULL);
		if (FAILED(result2))
		{
			throw new GameError(GameErrorNS::FATAL_ERROR, "Cannot create tilemap surface!");
		}

		result2 = device3D->GetRenderTargetData(pViewportSurface, pSurface);
		if (FAILED(result2))
		{
			throw new GameError(GameErrorNS::FATAL_ERROR, "Cannot get render target data!");
		}

		HRESULT result = D3DXCreateTexture(
			device3D,
			viewportSurfaceWidth,
			viewportSurfaceHeight,
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
			pViewportSurface->Release();
		}

		
		//D3DXSaveTextureToFile("renderViewportTexture.png", D3DXIMAGE_FILEFORMAT::D3DXIFF_PNG, m_tileMapTexture, NULL);

		Texture *texture = new Texture(m_tag, m_tileMapTexture, viewportSurfaceWidth, viewportSurfaceHeight);
		RegisterTexture(m_tag, texture);
	}
}