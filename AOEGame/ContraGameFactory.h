#ifndef __CONTRAGAME_FACTORY_H__
#define __CONTRAGAME_FACTORY_H__

#include "Framework\Utilities\Singleton.h"
#include "Framework\GameObjects\GameObject.h"
#include "Framework\TileMap\TileMap.h"

class ContraGameFactory
	: public Framework::Singleton<ContraGameFactory>
{
public:
	ContraGameFactory() {};
	~ContraGameFactory() {};


	Framework::GameObject* GetPlayerObject();
	Framework::GameObject* GetTileMapObject(Framework::TileMap* tileMap);
	Framework::GameObject* GetTileMapObjectMap1Scene2(Framework::TileMap* tileMap);
	Framework::GameObject* GetNpcTestObject();
	Framework::GameObject* GetCameraObject(Framework::GameObject* attachObj);
};
#endif