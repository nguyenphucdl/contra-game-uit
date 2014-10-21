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

		void				SetBoundMin(const Vector3& min)	{ m_min = min;  }
		const Vector3&		GetBoundMin() const					{ return m_min; }	

		void				SetBoundMax(const Vector3&	max)	{ m_max = max;  }
		const Vector3&		GetBoundMax() const					{ return m_max;	}

		void				SetUseBounds(bool enabled)			{ m_useBounds = enabled;	}
		bool				GetUseBounds() const				{ return m_useBounds;	}

		//bool				IsInitialized() const { return m_pGeometry; }
	};

	inline Renderable::Renderable()
		: m_pTextureRegion(NULL)
		, m_useBounds(false)
		, m_zIndex(RenderableIndex::OBJECT_INDEX)
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
}
#endif