#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <d3d9.h>
#include <d3dx9.h>

#include "../Platform/Window.h"
#include "../Application/Context.h"
#include "../Renderer/Texture/TextureManager.h"
#include "Renderable.h"
#include "Camera.h"
#include "Drawable.h"

// DirectX pointer types
#define	LP_D3DEVICE			LPDIRECT3DDEVICE9
#define LP_3D				LPDIRECT3D9
#define LP_BACKBUFFER		LPDIRECT3DSURFACE9
#define LP_SPRITEHANDLER	LPD3DXSPRITE

namespace Framework
{

	class Renderer 
		:	public Task
		,	public Singleton<Renderer>
	{
	private:
		/*DirectX Specific*/
		bool						m_initialized;
		LP_3D						m_direct3d;
		LP_D3DEVICE					m_device3d;
		LP_BACKBUFFER				m_backbuffer;
		LP_SPRITEHANDLER			m_spriteHandler;
		D3DPRESENT_PARAMETERS		m_d3dpp;
		D3DDISPLAYMODE				m_displayMode;
		HRESULT						m_result;
		HWND						m_hwnd;
		bool						m_fullScreen;
		int							m_width;
		int							m_height;
		COLOR_ARGB					m_backColor;

		
		/*Render states*/
		typedef std::vector<Renderable*>		RenderableVector;
		typedef	RenderableVector::iterator		RenderableVectorIterator;
		typedef std::vector<Drawable*>			DrawableVector;
		typedef DrawableVector::iterator		DrawableVectorIterator;

		RenderableVector					m_renerables;
		DrawableVector						m_drawables;
	
		Camera								m_camera;


		D3DXMATRIX							m_worldViewMatrix;
		D3DXMATRIX							m_transformCoordinateMatrix; // flip & translate coordinate
		D3DXMATRIX							m_viewMatrix;
		/*Debug texture*/
		Texture*							m_debugTexture;

	public:
		explicit Renderer(const unsigned int priority);
		virtual ~Renderer();

		void Init();
		void Destroy();

		void AddRenderable(Renderable* pRenderable);
		void RemoveRenderable(Renderable* pRenderable);	
		void AddDrawable(Drawable* pDrawable);
		void RemoveDrawble(Drawable* pDrawable);

		// From Task
		virtual	bool	Start();
		virtual	void	OnSuspend();
		virtual void	Update();
		virtual void	OnResume();
		virtual void	Stop();

		bool IsInitialized()	{ return m_initialized; }
		// Handle lost graphics device
		virtual void handleLostGraphicsDevice();
		// Return handle to device context (window)
		HDC		getDC()	{ return GetDC(m_hwnd); }

		// get functions
		LP_D3DEVICE	getD3device()					{ return m_device3d; }	
		LP_3D		get3D()							{ return m_direct3d; }
		Camera&		GetCamera()						{ return m_camera;	 }
		int			GetWidth()						{ return m_width; }
		int			GetHeight()						{ return m_height; }

	private:
		void	Draw(Renderable* pRenderable);
		
		void	InitTransformCoordinateMatrix();
		void	PrepareViewMatrix();

		void	releaseAll();
		void	initD3Dpp();
		bool	isAdapterCompatible();
		
		HRESULT showBackBuffer();	// Display the offscreen backbuffer to the screen
		HRESULT reset();			// Reset the graphics device
		HRESULT	getDeviceState();	// Test for lost device
		

		//=============================================================================
		// Inline functions for speed. How much more speed? It depends on the game and
		// computer. Improvements of 3 or 4 percent have been observed.
		//=============================================================================

		// Set color used to clear screen
		void setBackColor(COLOR_ARGB c) { m_backColor = c; }

		//=============================================================================
		// Clear backbuffer and BeginScene()
		//=============================================================================
		HRESULT beginScene()
		{
			m_result = E_FAIL;
			if(m_device3d == NULL)
				return m_result;
			
			//m_device3d->Clear(0, NULL, D3DCLEAR_TARGET, m_backColor, 1.0F, 0);
			m_result = m_device3d->BeginScene();
			// clear backbuffer to backcolor
			m_device3d->ColorFill(m_backbuffer, NULL, m_backColor);

			return m_result;
		}

		//=============================================================================
		// EndScene()
		//=============================================================================
		HRESULT endScene()
		{
			m_result = E_FAIL;
			if(m_device3d)
				m_result = m_device3d->EndScene();
			return m_result;
		}
	};
}


#endif//__RENDERER_H__