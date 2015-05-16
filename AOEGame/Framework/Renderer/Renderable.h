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
		const int OBJECT_INDEX = 100;
		const int POWERUP_INDEX = 150;
	}
	
	class Renderable
	{
	private:
		//Geometry*				m_pGeometry;         Rectangle, Eclipse, Oval, Triangle ...
		TextureRegion*			m_pTextureRegion;
		Transform				m_transform;
		Vector3					m_origin;
		bool					m_renderTrans;// Enable OR Disable transform
		bool					m_visible;
		std::string				m_tag;
		bool					m_debug;
		int						m_width;
		int						m_height;

		// Fulture use only
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

		void				SetBoundMin(const Vector3& min)	{ m_min = min; }
		Vector3&			GetBoundMin();

		void				SetBoundMax(const Vector3&	max)	{ m_max = max; }
		Vector3&			GetBoundMax();

		void				SetUseBounds(bool enabled)			{ m_useBounds = enabled; }
		bool				GetUseBounds() const				{ return m_useBounds; }

		void				SetTag(std::string tagName)			{ m_tag = tagName; }
		std::string			GetTag()							{ return m_tag; }

		void				SetDebug(bool debug)				{ m_debug = debug;		}
		bool				IsDebug()							{ return m_debug;		}

		Vector3&			GetOrigin()							{ return m_origin;		}

		void				SetOrigin(Vector3& origin)			{ m_origin = origin;	}
		void				SetOrigin(int x, int y, int z)		{ m_origin.m_x = x; m_origin.m_y = y, m_origin.m_z = z; }

		bool				GetRenderTransform()						{ return m_renderTrans; }
		void				SetRenderTransform(bool renderTrans)		{ m_renderTrans = renderTrans; }

		void				IsVisible(bool visible)				{ m_visible = visible; }
		bool				IsVisible()							{ return m_visible; }

		void				SetZIndex(int idx)					{ m_zIndex = idx; }
		int					GetZIndex()							{ return m_zIndex; }

		Vector3				GetPosition();
		void				SetSize(int width, int height)		{ m_width = width; m_height = height; }
		int					GetWidth()							{ return m_width;  }
		int					GetHeight()							{ return m_height; }

		//bool				IsInitialized() const { return m_pGeometry; }
	};

	inline Renderable::Renderable()
		: m_pTextureRegion(NULL)
		, m_useBounds(false)
		, m_zIndex(RenderableIndex::OBJECT_INDEX)
		, m_renderTrans(true)
		, m_origin(0, 0, 0)
		, m_visible(true)
		, m_tag("")
		, m_debug(true)
		, m_width(0)
		, m_height(0)
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
		Vector3 position = m_origin;
		if (m_renderTrans)
		{
			Transform::Vector3Transform(&m_origin, &position, &m_transform);
		}
		return position;
	}
	inline Vector3& Renderable::GetBoundMin()
	{
		Vector3 boundmin = m_origin;
		Transform::Vector3Transform(&m_origin, &boundmin, &m_transform);
		boundmin.Add(m_min);
		return boundmin;
	}
	inline Vector3& Renderable::GetBoundMax()
	{
		Vector3 boundmin = m_origin;
		Transform::Vector3Transform(&m_origin, &boundmin, &m_transform);
		boundmin.Add(m_min);
		Vector3 boundmax = boundmin;
		boundmax.Add(m_max);
		return boundmax;
	}

}
#endif