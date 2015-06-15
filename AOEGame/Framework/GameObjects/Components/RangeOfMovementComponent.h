#ifndef __RANGEOFMOVEMENT_COMPONENT_H__
#define	__RANGEOFMOVEMENT_COMPONENT_H__

#include "../Component.h"
#include "../../Utilities/Enums.h"

namespace Framework
{
	class RangeOfMovementComponent
		: public Component
	{
	private:
		static const unsigned int	s_id = ComponentIDs::RangeOfMovementComponentId;

		virtual void Initialize();

		int m_objectTarget;

	public:
		static unsigned int GetId()		 { return s_id; }

		explicit RangeOfMovementComponent(GameObject* pOwner);
		virtual ~RangeOfMovementComponent();

		int		GetObjectTarget()		 { return m_objectTarget; }
		void	SetObjectTarget(int id)	 { m_objectTarget = id; }
	};
}

#endif