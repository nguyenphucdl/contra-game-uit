#ifndef __CONTRAGAME_FACTORY_H__
#define __CONTRAGAME_FACTORY_H__

#include "Framework\Utilities\Singleton.h"
#include "Framework\GameObjects\GameObject.h"
#include "Framework\TileMap\TileMap.h"
#include "Framework\Utilities\ObjectFactory.h"

class CommonGameFactory
	: public Framework::Singleton<CommonGameFactory>
	, public Framework::ObjectFactory
{
public:
	CommonGameFactory() {};
	virtual ~CommonGameFactory() {};


	Framework::GameObject* GetPlayerObject();
	Framework::GameObject* GetTileMapObject(Framework::TileMap* tileMap);
	Framework::GameObject* GetCameraObject(Framework::GameObject* attachObj);

	

	//Framework::GameObject* GetTileMapObjectMap1Scene2(Framework::TileMap* tileMap);
	//Framework::GameObject* GetNpcTestObject();

protected:
	void _createPlayerObject(Framework::GameObject* owner, void* pData = NULL);
	void _createTileMapObject(Framework::GameObject* owner, Framework::TileMap* pTileMap);
	void _createCameraObject(Framework::GameObject* owner, Framework::GameObject* pAttachObj);

	virtual void createObjectType(std::string objectType, Framework::GameObject* owner, void* pData = NULL) = 0;
};
#endif