#include "Camera.h"

namespace Framework
{
	Camera::Camera()
		:	m_viewOrigin(0, 0, 0)
		, m_viewTranslate(0, 0, 0)
		, m_viewWidth(0)
		, m_viewHeight(0)
	{
		
	}

	Camera::~Camera()
	{
	}

	void Camera::SetViewPortOrigin(int x, int y)
	{
		this->m_viewOrigin.m_x = x;
		this->m_viewOrigin.m_y = y;
	}

	void Camera::SetViewTranslate(Vector3* translate)
	{
		this->m_viewTranslate.Set(*translate);
	}

	void Camera::SetWidth(int width)
	{
		m_viewWidth = width;
	}

	void Camera::SetHeight(int height)
	{
		m_viewHeight = height;
	}

	RECT& Camera::GetViewPort()
	{
		Vector3 pos = m_viewOrigin;
		pos.Add(m_viewTranslate);
		RECT result;
		result.left = pos.m_x;
		result.right = result.left + m_viewWidth;
		result.top = pos.m_y;
		result.bottom = result.top + m_viewHeight;
		return result;
	}

	void Camera::ResetViewport()
	{
		m_viewTranslate.m_x = 0;
		m_viewTranslate.m_y = 0;
		m_viewTranslate.m_z = 0;
	}
}