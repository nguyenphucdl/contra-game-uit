#ifndef __OBJECT_FACTORY_H__
#define	__OBJECT_FACTORY_H__

#include "../GameObjects/GameObject.h"
#include "ObjectMapData.h"

namespace Framework
{
	class  ObjectFactory
	{
	public:
		virtual void createObjectType(std::string objectType, GameObject* owner, void* pData = NULL) = 0;

	};
}
#endif