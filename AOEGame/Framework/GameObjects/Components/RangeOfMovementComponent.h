#ifndef __RANGEOFMOVEMENT_COMPONENT_H__
#define	__RANGEOFMOVEMENT_COMPONENT_H__

#include<vector>
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

		std::vector<int>	m_objectsInRange;

	public:
		static unsigned int GetId()		 { return s_id; }

		explicit RangeOfMovementComponent(GameObject* pOwner);
		virtual ~RangeOfMovementComponent();

		const std::vector<int>*		GetObjectsInRange()		 { return &m_objectsInRange; }
		void  AddObjectInRange(int objId) { m_objectsInRange.push_back(objId); }
		void  ClearObjectInRange() { m_objectsInRange.clear(); }
	};
}

#endif