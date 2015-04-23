#include "Renderer.h"
#include "../EventManager/EventManager.h"
#include <math.h>

namespace Framework
{
	Renderer::Renderer(const unsigned int priority)
		: Task(priority, "Renderer Task")
		, m_direct3d(NULL)
		, m_device3d(NULL)
		, m_fullScreen(false)
	{
		m_width = GameConfig::GetSingletonPtr()->GetInt("GAME_WIDTH");
		m_height = GameConfig::GetSingletonPtr()->GetInt("GAME_HEIGHT");
		m_backColor = SETCOLOR_ARGB(255,0,0,128); // dark blue
	}

	Renderer::~Renderer()
	{
		releaseAll();
	}

	void Renderer::releaseAll()
	{
		SAFE_RELEASE(m_device3d);
		SAFE_RELEASE(m_direct3d);
	}

	void Renderer::Init()
	{
		m_hwnd = Window::GetSingletonPtr()->GetWindowHandle();
		m_width = GameConfig::GetSingletonPtr()->GetInt(ConfigKey::GAME_WIDTH);
		m_height = GameConfig::GetSingletonPtr()->GetInt(ConfigKey::GAME_HEIGHT);
		m_fullScreen = GameConfig::GetSingletonPtr()->GetBool(ConfigKey::FULLSCREEN);


		//initialize Direct3D
		m_direct3d = Direct3DCreate9(D3D_SDK_VERSION);
		if(m_direct3d == NULL)
			throw(GameError(GameErrorNS::FATAL_ERROR, "Error initializing Direct3D"));
		initD3Dpp();					// init D3D presentation parameters
		if(m_fullScreen)				// if full-screen mode
		{
			if(isAdapterCompatible())	// is the adapter compatible
				// set the refresh rate with a compatible one
				m_d3dpp.FullScreen_RefreshRateInHz = m_displayMode.RefreshRate;
			else
				throw(GameError(GameErrorNS::FATAL_ERROR, 
				 "The graphics device does not support the specified resolution and/or format."));
		}

		// determine if graphics card supports harware texturing and lighting and vertex shaders
		D3DCAPS9 caps;
		DWORD	 behavior;
		m_result = m_direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
		// If device doesn't support HW T&L or doesn't support 1.1 vertex 
		// shaders in hardware, then switch to software vertex processing.
		if( (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
            caps.VertexShaderVersion < D3DVS_VERSION(1,1) )
			behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;  // use software only processing
		else
			behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;  // use hardware only processing

		// create Direct3D device
		m_result = m_direct3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			m_hwnd,
			behavior,
			&m_d3dpp,
			&m_device3d);
		
		if(FAILED(m_result))
			throw(GameError(GameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));

		m_device3d->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backbuffer);

		m_result = D3DXCreateSprite(m_device3d, &m_spriteHandler);
		if(FAILED(m_result))
			throw(GameError(GameErrorNS::FATAL_ERROR, "Error creating Direct3D sprite handler"));
		/*Setting Camera*/
		m_camera.SetWidth(m_width);
		m_camera.SetHeight(m_height);

		/*REGISTER EVENT*/
		RegisterEvent(Events::PRE_RENDER_EVENT);
		RegisterEvent(Events::RENDER_EVENT);
	}
	//=============================================================================
	// Initialize D3D presentation parameters
	//=============================================================================
	void Renderer::initD3Dpp()
	{
		try
		{
			ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));				// fill the structure with 0
			// fill in the parameters we need
			m_d3dpp.BackBufferWidth			= m_width;
			m_d3dpp.BackBufferHeight		= m_height;
			if(m_fullScreen)									// if fullscreen
				m_d3dpp.BackBufferFormat	= D3DFMT_X8R8G8B8;	// 24 bit color
			else
				m_d3dpp.BackBufferFormat	= D3DFMT_UNKNOWN;		// use desktop setting
			m_d3dpp.BackBufferCount			= 1;
			m_d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
			m_d3dpp.hDeviceWindow			= m_hwnd;
			m_d3dpp.Windowed				= (!m_fullScreen);
			m_d3dpp.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;
		}catch(...)
		{
			throw(GameError(GameErrorNS::FATAL_ERROR, 
                "Error initializing D3D presentation parameters"));
		}
	}

	//=============================================================================
	// Checks the adapter to see if it is compatible with the BackBuffer height,
	// width and refresh rate specified in d3dpp. Fills in the pMode structure with
	// the format of the compatible mode, if found.
	// Pre: d3dpp is initialized.
	// Post: Returns true if compatible mode found and pMode structure is filled.
	//       Returns false if no compatible mode found.
	//=============================================================================
	bool Renderer::isAdapterCompatible()
	{
		UINT modes = m_direct3d->GetAdapterModeCount(D3DADAPTER_DEFAULT, 
													m_d3dpp.BackBufferFormat);
		for(UINT i = 0; i < modes; i++)
		{
			m_result = m_direct3d->EnumAdapterModes(D3DADAPTER_DEFAULT,
													m_d3dpp.BackBufferFormat,
													i, &m_displayMode);
			if(m_displayMode.Height == m_d3dpp.BackBufferHeight &&
				m_displayMode.Width == m_d3dpp.BackBufferWidth &&
				m_displayMode.RefreshRate >= m_d3dpp.FullScreen_RefreshRateInHz)
				return true;
		}
		return false;
	}

	void Renderer::AddRenderable(Renderable* pRenderable)
	{
		
		RenderableVectorIterator iter;
		for (iter = m_renerables.begin(); iter != m_renerables.end(); ++iter)
		{
			Renderable* pCurrent = *iter;
			if (pCurrent == pRenderable)
			{
				return;
			}
			if (pCurrent->GetZIndex() > pRenderable->GetZIndex())
			{
				break;
			}
		}
		Log::info(Log::LOG_LEVEL_ROOT, "[Renderer] AddRenderable level %d... !\n", pRenderable->GetZIndex());
		m_renerables.insert(iter, pRenderable);
	}

	void Renderer::RemoveRenderable(Renderable* pRenderable)
	{
		for(RenderableVectorIterator iter = m_renerables.begin(); iter != m_renerables.end(); ++iter)
		{
			Renderable* pCurrent = *iter;
			if(pCurrent == pRenderable)
			{
				m_renerables.erase(iter);
				break;
			}
		}
	}

	void Renderer::AddDrawable(Drawable* pDrawable)
	{
		DrawableVectorIterator iter;
		for (iter = m_drawables.begin(); iter != m_drawables.end(); ++iter)
		{
			Drawable* pCurrent = *iter;
			if (pCurrent == pDrawable)
			{
				return;
			}
			/*if (pCurrent->GetZIndex() > pRenderable->GetZIndex())
			{
				break;
			}*/
		}
		m_drawables.insert(iter, pDrawable);
	}

	void Renderer::RemoveDrawble(Drawable* pDrawable)
	{
		for (DrawableVectorIterator iter = m_drawables.begin(); iter != m_drawables.end(); ++iter)
		{
			Drawable* pCurrent = *iter;
			if (pCurrent == pDrawable)
			{
				m_drawables.erase(iter);
				break;
			}
		}
	}

	//=============================================================================
	// Display the backbuffer
	//=============================================================================
	HRESULT Renderer::showBackBuffer()
	{
		m_result = E_FAIL;		// fefault to fail, replace on success
		// Display backbuffer to screen
		m_result = m_device3d->Present(NULL, NULL, NULL, NULL);
		return m_result;
	}

	//=============================================================================
	// Reset the graphics device
	//=============================================================================
	HRESULT Renderer::reset()
	{
		m_result = E_FAIL;		//default to fail, replace on success
		initD3Dpp();			//init D3D presentation parameters
		m_result = m_device3d->Reset(&m_d3dpp);
		return m_result;
	}

	//=============================================================================
	// Draw renderable
	//=============================================================================
	void Renderer::Draw(Renderable* pRenderable)
	{
		assert(pRenderable);
		if(pRenderable)
		{
			D3DXVECTOR3 pos = pRenderable->GetPosition().GetD3DVector();

			D3DXVECTOR3 posTransform = Transform::GetVector3FromWorldView(pos, m_transformCoordinateMatrix);
			D3DXVECTOR4 posInScreenCoord(posTransform.x, posTransform.y, posTransform.z, 1);
			

			/*if (pRenderable->GetTag() != "TileMap" && pRenderable->GetRenderTransform())
			{
				D3DXVec3Transform(&posInScreenCoord, &posTransform, &m_viewMatrix);
			}*/

			if (pRenderable->GetRenderTransform())
			{
				//D3DXMATRIX _result;
				//D3DXMatrixIdentity(&_result);
				//D3DXMatrixMultiply(&_result, &m_transformCoordinateMatrix, &m_viewMatrix);
				D3DXVec3Transform(&posInScreenCoord, &posTransform, &m_viewMatrix);
			}
			
			



			TextureRegion *texture = pRenderable->GetTextureRegion();
			RECT srcRect = texture->GetRect();

			if (pRenderable->IsVisible())
			{
				m_spriteHandler->Draw(texture->GetTexture()->GetTexture(), &srcRect, NULL, &D3DXVECTOR3(posInScreenCoord.x, posInScreenCoord.y, posInScreenCoord.z), D3DCOLOR_XRGB(255, 255, 255));
			}

			if (pRenderable->IsDebug())
			{
				int textureW = abs(texture->GetRect().right - texture->GetRect().left);
				int textureH = abs(texture->GetRect().top - texture->GetRect().bottom);

				float scaleX = (float)textureW / 200;
				float scaleY = (float)textureH / 200;

				D3DXVECTOR2 scaleVector(scaleX, scaleY);
				D3DXVECTOR2 centerVector((float)(200 * scaleX) / 2, (float)(200 * scaleY) / 2);
				D3DXVECTOR2 trans((float)posInScreenCoord.x, (float)posInScreenCoord.y);
				D3DXMATRIX  viewMatrix;
				D3DXMatrixIdentity(&viewMatrix);
				D3DXMatrixTransformation2D(&viewMatrix, NULL, 0, &scaleVector, &centerVector, 0, &trans);

				m_spriteHandler->SetTransform(&viewMatrix);

				m_spriteHandler->Draw(m_debugTexture->GetTexture(), NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
				//restore matrix
				m_spriteHandler->SetTransform(&m_worldViewMatrix);
			}
		}
	}


	//=============================================================================
	// Test for lost device
	//=============================================================================
	HRESULT Renderer::getDeviceState()
	{
		m_result = E_FAIL;		// default to fail, replace on success
		if(m_device3d == NULL)
			return	m_result;
		m_result = m_device3d->TestCooperativeLevel();
		return m_result;
	}

	void Renderer::handleLostGraphicsDevice()
	{
		// test for and handle lost device
		m_result = this->getDeviceState();
		if(FAILED(m_result))		// if graphics device is not in a valid state
		{
			Log::info(Log::LOG_LEVEL_ROOT, "[Renderer][handleLostGraphicsDevice] Lost device...\n");

			// if the device is lost and not available for reset
			if(m_result == D3DERR_DEVICELOST)
			{
				Sleep(100);					// yield cpu time (100 mili-seconds)
				return;
			}
			// the device was lost but is now available for reset
			else if(m_result == D3DERR_DEVICENOTRESET)
			{
				//this->releaseAll();
				m_result = this->reset();	// attempt to reset graphics device
				if(FAILED(m_result))		// if reset failed
					return;
				Log::info(Log::LOG_LEVEL_ROOT, "[Renderer][handleLostGraphicsDevice] Acquire device successfully!\n");
			}
		}
	}

	// From Task
	bool Renderer::Start()
	{
		Log::info(Log::LOG_LEVEL_ROOT, "[Renderer][Start] Starting...\n");

		Init();
		InitWorldViewMatrix();
		
		RegisterTexture("Resources\\debug-texture.png");
		m_debugTexture = GetTexture("debug-texture.png");
		return true;
	}
	void Renderer::OnSuspend()
	{
	}
	void Renderer::Update()
	{	
		if(SUCCEEDED(this->beginScene()))
		{
			// Begin sprite handler
			m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

			// Set world matrix
			m_spriteHandler->SetTransform(&m_worldViewMatrix);

			PrepareViewMatrix();

			// Send PRE_RENDER_EVENT
			Framework::SendEvent(Events::PRE_RENDER_EVENT);

			// Draw 2D [FULTURE: renderable object get from scene grapth]
			for(RenderableVectorIterator iter = m_renerables.begin(); iter != m_renerables.end(); ++iter)
			{
				Renderable* pRenderable = *iter;
				if(pRenderable)
				{
					Draw(pRenderable);
				}
			}

			// Custom draw handler
			for (DrawableVectorIterator iter = m_drawables.begin(); iter != m_drawables.end(); ++iter)
			{
				Drawable* pDrawable = *iter;
				if (pDrawable)
				{
					pDrawable->Draw(m_spriteHandler);
				}
			}
			

			// end sprite handler
			m_spriteHandler->End();

			// stop rendering
			this->endScene();
		}
		this->handleLostGraphicsDevice();
		this->showBackBuffer();
	}

	void Renderer::InitWorldViewMatrix()
	{
		// flip coordinate system
		D3DXMATRIX flipYMatrix, translateMatrix;
		D3DXMatrixIdentity(&flipYMatrix);
		D3DXMatrixIdentity(&translateMatrix);
		flipYMatrix._22 = -1;
		translateMatrix._42 = 480;
		D3DXMatrixMultiply(&m_transformCoordinateMatrix, &flipYMatrix, &translateMatrix);

		// prepare world view matrix
		D3DXMatrixIdentity(&m_worldViewMatrix);
	}

	void Renderer::PrepareViewMatrix()
	{
		Vector3	inverseViewTranslate = m_camera.GetViewTranslate().GetInverse();
		D3DXMatrixIdentity(&m_viewMatrix);
		D3DXMatrixTransformation2D(&m_viewMatrix, NULL, 0, NULL, 0, 0, &D3DXVECTOR2(inverseViewTranslate.m_x, inverseViewTranslate.m_y));
	}

	void Renderer::OnResume()
	{
	}
	void Renderer::Stop()
	{
	}	
}