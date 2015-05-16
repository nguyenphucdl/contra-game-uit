#ifndef __CAMERA_H__
#define	__CAMERA_H__

#include <d3d9.h>
#include <d3dx9.h>
#include "../Application/Context.h"

namespace Framework
{
	class Camera
	{
	private:	
		Vector3			m_viewOrigin;
		Vector3			m_viewTranslate;
		int				m_viewWidth;
		int				m_viewHeight;

		RECT			m_viewPort;
	public:
		explicit Camera();
		~Camera();

		void			SetViewPortOrigin(int x, int y);
		void			SetViewTranslate(Vector3* translate);
		void			SetWidth(int width);
		void			SetHeight(int height);
		void			ResetViewport();

		RECT&			GetViewPort();
		int				GetViewPortWidth()		{ return m_viewWidth; }
		int				GetViewPortHeight()		{ return m_viewHeight; }
		Vector3			GetViewOrigin()			{ return m_viewOrigin; }
		Vector3			GetViewTranslate()		{ return m_viewTranslate; }

	};
}

#endif