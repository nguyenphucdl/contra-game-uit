#ifndef __EVENTID_H__
#define __EVENTID_H__

#include "../Utilities/Enums.h"
namespace Framework
{
	class GameObject;

	struct CollisionEventData
	{
		GameObject* m_pCollider;
	};

}
#endif