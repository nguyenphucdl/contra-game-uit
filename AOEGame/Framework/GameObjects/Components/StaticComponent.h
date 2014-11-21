#ifndef __STATICCOMPONENT_H__
#define	__STATICCOMPONENT_H__

#include "../../Application/Context.h"
#include "../GameObject.h"

namespace Framework
{
	class StaticComponent
		: public Component
	{
	private:
		static const unsigned int	s_id = 5;

		RECT m_bound;
	public:
		static unsigned int GetId() { return s_id; }

		explicit StaticComponent(GameObject* pOwner);
		virtual ~StaticComponent();

		virtual void Initialize();

		RECT&	GetBound()		{ return m_bound; }
		void	SetBound(RECT bound) { m_bound = bound; }
	};
}
#endif//__STATICCOMPONENT_H__