#include "Renderer.h"

namespace Framework
{
	Renderer::Renderer(const unsigned int priority)
		: Task(priority, "Renderer Task")
		, m_direct3d(NULL)
		, m_device3d(NULL)
		, m_fullScreen(false)
		, m_viewOrigin(0, 0, 0)
		, m_viewTranslate(0, 0, 0)
		, m_viewTransform()
		
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

		RegisterTexture("debug-texture.png");
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
			Vector3 posVector = pRenderable->GetPosition();
			D3DXVECTOR3 pos = posVector.GetD3DVector();

			D3DXVECTOR3 posTransform = Transform::GetVector3FromWorldView(pos, m_worldViewMatrix);


			if (pRenderable->IsVisible())
			{
				TextureRegion *texture = pRenderable->GetTextureRegion();
				m_spriteHandler->Draw(texture->GetTexture()->GetTexture(), &texture->GetRect(), NULL, &posTransform, D3DCOLOR_XRGB(255, 255, 255));
			}
			

			//debug
			Texture* debugTexture = GetTexture("debug-texture.png");
			RECT debugsrc;
			debugsrc.left = 0;
			debugsrc.right = debugTexture->GetWidth();
			debugsrc.top = 0;
			debugsrc.bottom = debugTexture->GetHeight();
			m_spriteHandler->Draw(debugTexture->GetTexture(), &debugsrc, NULL, &posTransform, D3DCOLOR_XRGB(255, 255, 255));

		}
	}

	void Renderer::DrawDebug(Renderable* pRenderable)
	{

	}

	void Renderer::AddDebug(DEBUG_REGION region)
	{
		m_debugRegions.push_back(region);
	}

	void Renderer::RemoveDebug(DEBUG_REGION region)
	{
		for (DebugRegionVectorIterator iter = m_debugRegions.begin(); iter != m_debugRegions.end(); ++iter)
		{
			DEBUG_REGION current = *iter;
			if (current.left == region.left && current.right == region.right 
				&& current.bottom == region.bottom && current.top == region.top)
			{
				m_debugRegions.erase(iter);
				break;
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
		Log::info(Log::LOG_LEVEL_ROOT, "[Renderer][Start] Entering...\n");
		Init();

		return true;
	}
	void Renderer::OnSuspend()
	{
	}
	void Renderer::Update()
	{	

		if(SUCCEEDED(this->beginScene()))
		{
			// render custom task
			//Log::info(Log::LOG_LEVEL_ROOT, "[Renderer] Updating... !\n");

			// begin sprite handler
			m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
			

			//m_spriteHandler->SetTransform(&resultMatrix);

			D3DXMATRIX flipYMatrix, translateMatrix;
			D3DXMatrixIdentity(&flipYMatrix);
			D3DXMatrixIdentity(&translateMatrix);
			flipYMatrix._22 = -1;
			translateMatrix._42 = 480;
			D3DXMatrixMultiply(&m_worldViewMatrix, &flipYMatrix, &translateMatrix);

			// draw 2D 
			for(RenderableVectorIterator iter = m_renerables.begin(); iter != m_renerables.end(); ++iter)
			{
				Renderable* pRenderable = *iter;
				if(pRenderable)
				{
					Draw(pRenderable);
				}
			}

			m_spriteHandler->End();
			// end sprite handler
			
			

			// stop rendering
			this->endScene();
		}
		
		this->handleLostGraphicsDevice();
		

		this->showBackBuffer();
	}
	void Renderer::OnResume()
	{
	}
	void Renderer::Stop()
	{
	}
	
	RECT& Renderer::GetViewport()
	{
		Vector3 pos = m_viewOrigin;
		pos.Add(m_viewTranslate);
		RECT result;
		result.left = pos.m_x;
		result.right = result.left + m_width;
		result.top = pos.m_y;
		result.bottom = result.top + m_height;
		return result;
	}

	void Renderer::SetViewportOrigin(int x, int y)
	{
		m_viewOrigin.m_x = x;
		m_viewOrigin.m_y = y;
	}

	void Renderer::ResetViewport()
	{
		m_viewTranslate.Set(0, 0, 0);
	}

	void Renderer::UpdateViewport(Vector3* translate)
	{
		m_viewTranslate.Set(translate->m_x, translate->m_y, translate->m_z);
	}

	Transform& Renderer::GetViewTransform()
	{
		return m_viewTransform;
	}

	void Renderer::UpdateViewTransform(Transform* trans)
	{
		m_viewTransform.Clone(*trans);
	}
}