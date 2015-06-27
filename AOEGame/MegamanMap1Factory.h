#ifndef __MEGAMAN_MAP1_FACTORY_H__
#define __MEGAMAN_MAP1_FACTORY_H__

#include "Framework\Application\Context.h"
#include "Framework\GameObjects\GameObject.h"
#include "CommonGameFactory.h"

class MegamanMap1Factory
	: public CommonGameFactory
{
public:
	MegamanMap1Factory();
	~MegamanMap1Factory();

	void createObjectType(std::string objectType, Framework::GameObject* owner, void* pData = NULL);

private:
	void _createLittlePogobot(Framework::GameObject* owner, void* data = NULL);
	void _createAnotherBot(Framework::GameObject* owner, void* data = NULL);
	void _createNapalmBomb(Framework::GameObject* owner, void* data = NULL);
	void _createFiveStarShooter(Framework::GameObject* owner, void* data = NULL);
	void _createWallShooter(Framework::GameObject* owner, void* data = NULL);
	void _createGreenRobocop(Framework::GameObject* owner, void* data = NULL);
	void _createBossBombMan(Framework::GameObject* owner, void* data = NULL);
};


#endif