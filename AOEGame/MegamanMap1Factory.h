#ifndef __MEGAMAN_MAP1_FACTORY_H__
#define __MEGAMAN_MAP1_FACTORY_H__

#include "Framework\Application\Context.h"
#include "Framework\GameObjects\GameObject.h"
#include "Framework\Utilities\ObjectFactory.h"

class MegamanMap1Factory
	: public Framework::ObjectFactory
{
public:
	MegamanMap1Factory();
	~MegamanMap1Factory();

	void createObjectType(std::string objectType, Framework::GameObject* owner, void* pData = NULL);

private:
	void _createLittlePogobot(Framework::GameObject* owner, void* data = NULL);
};


#endif