#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include "../Application/Context.h"
#include "../Math/Transform.h"
#include "Texture\TextureRegion.h"

namespace Framework
{
	namespace RenderableIndex
	{
		const int BACKGROUND_INDEX = 50;
		const int OBJECT_INDEX_LOW = 100;
		const int OBJECT_INDEX_MEDIUM = 150;
		const int OBJECT_INDEX_HIGH = 200;
		const int POWERUP_INDEX = 250;
	}
	
	class Renderable
	{
	private:
		//Geometry*				m_pGeometry;         Rectangle, Eclipse, Oval, Triangle ...
		TextureRegion*			m_pTextureRegion;
		Transform				m_transform;
		bool					m_renderTrans;// Enable OR Disable transform
		bool					m_visible;
		std::string				m_tag;
		bool					m_debug;
		int						m_width;
		int						m_height;
		Vector3					m_center;
		bool					m_isDrawCenter;

		// Collision
		Vector3					m_min;
		Vector3					m_max;
		bool					m_useBounds;

		int						m_zIndex;

	public:
		explicit Renderable();
		~Renderable();

		TextureRegion*		GetTextureRegion();
		void				SetTextureRegion(TextureRegion* pTextureRegion);

		Transform&			GetTransform()						{ return m_transform; }
		void				SetTransform(Transform &pTransform)	{ m_transform = pTransform; }

		void				SetTranslation(Vector3& translate) { m_transform.SetTranslation(translate); }

		void				SetBoundMin(const Vector3& min)	{ m_min = min; }
		const Vector3&		GetBoundMin();

		void				SetBoundMax(const Vector3&	max)	{ m_max = max; }
		const Vector3&		GetBoundMax();

		void				SetUseBounds(bool enabled)			{ m_useBounds = enabled; }
		bool				GetUseBounds() const				{ return m_useBounds; }

		void				SetTag(std::string tagName)			{ m_tag = tagName; }
		std::string			GetTag()							{ return m_tag; }

		void				SetDebug(bool debug)				{ m_debug = debug;		}
		bool				IsDebug()							{ return m_debug;		}

		bool				GetRenderTransform()						{ return m_renderTrans; }
		void				SetRenderTransform(bool renderTrans)		{ m_renderTrans = renderTrans; }

		void				Show(bool visible)							{ m_visible = visible; }
		void				Hide()										{ m_visible = false; }
		bool				IsVisible()									{ return m_visible; }

		void				SetZIndex(int idx)					{ m_zIndex = idx; }
		int					GetZIndex()							{ return m_zIndex; }

		Vector3				GetPosition();
		void				SetSize(int width, int height)		{ m_width = width; m_height = height; }
		int					GetWidth()							{ return m_width;  }
		int					GetHeight()							{ return m_height; }

		bool				IsDrawCenter()						{ return m_isDrawCenter; }
		void				SetDrawCenter(bool val)				{ m_isDrawCenter = val; }
		Vector3				GetCenter()							{ return m_center; }
		void				SetCenter(float x, float y)			{ m_center.Set(x, y, 1.0f); }
	};

	inline Renderable::Renderable()
		: m_pTextureRegion(NULL)
		, m_useBounds(false)
		, m_zIndex(RenderableIndex::OBJECT_INDEX_MEDIUM)
		, m_renderTrans(true)
		, m_visible(true)
		, m_tag("")
		, m_debug(true)
		, m_width(0)
		, m_height(0)
		, m_center(0.0f, 0.0f, 1.0f)
		, m_isDrawCenter(false)
	{
	}
	inline Renderable::~Renderable()
	{
	}
	inline TextureRegion* Renderable::GetTextureRegion()
	{
		return m_pTextureRegion;
	}
	inline void Renderable::SetTextureRegion(TextureRegion* pTextureRegion)
	{
		m_pTextureRegion = pTextureRegion;
	}
	inline Vector3	Renderable::GetPosition()
	{
		return m_transform.GetTranslation();
	}
	inline const Vector3& Renderable::GetBoundMin()
	{
		return m_min;
	}
	inline const Vector3& Renderable::GetBoundMax()
	{
		return m_max;
	}

}
#endif