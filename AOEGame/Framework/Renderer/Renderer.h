#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <d3d9.h>
#include <d3dx9.h>

#include "../Platform/Window.h"
#include "Renderable.h"

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
		bool						m_initialized;
		// DirectX states
		LP_3D						m_direct3d;
		LP_D3DEVICE					m_device3d;
		LP_BACKBUFFER				m_backbuffer;
		LP_SPRITEHANDLER			m_spriteHandler;

		D3DPRESENT_PARAMETERS		m_d3dpp;
		D3DDISPLAYMODE				m_displayMode;

		// Another states
		HRESULT						m_result;
		HWND						m_hwnd;
		bool						m_fullScreen;
		int							m_width;
		int							m_height;
		COLOR_ARGB					m_backColor;
		// width & height & another states

		typedef std::vector<Renderable*>		RenderableVector;
		typedef	RenderableVector::iterator	RenderableVectorIterator;

		RenderableVector					m_renerables;
	
		Matrix4								m_projectionMatrix;
		Matrix4								m_viewMatrix;
		//test
		bool								m_camera;
		bool								m_iinit;
		D3DXVECTOR3 posView ;
		D3DXVECTOR3 updir;
		D3DXVECTOR3 target;
	public:
		explicit Renderer(const unsigned int priority);
		virtual ~Renderer();

		void Init();
		void Destroy();

		void AddRenderable(Renderable* pRenderable);
		void RemoveRenderable(Renderable* pRenderable);
		
		// From Task
		virtual	bool	Start();
		virtual	void	OnSuspend();
		virtual void	Update();
		virtual void	OnResume();
		virtual void	Stop();

		// Matrix
		const Matrix4&	GetProjectionMatrix() const;
		void			SetProjectionMatrix(const Matrix4& proj);

		const Matrix4&	GetViewMatrix() const;
		void			SetViewMatrix(const Matrix4& view);

		bool IsInitialized()	{ return m_initialized; }
		// Handle lost graphics device
		virtual void handleLostGraphicsDevice();
		// Return handle to device context (window)
		HDC		getDC()	{ return GetDC(m_hwnd); }

		// get functions
		LP_D3DEVICE	getD3device()	{ return m_device3d; }	
		LP_3D		get3D()			{ return m_direct3d; }

	public://test public
		void	Draw(Renderable* pRenderable);
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