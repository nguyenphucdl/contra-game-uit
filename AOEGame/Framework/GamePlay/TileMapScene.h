#ifndef __TILEMAP_SCENE_H__
#define __TILEMAP_SCENE_H__
#include "../Application/Context.h"
#include "SceneBase.h"
#include "../GameObjects/GameObject.h"
#include "../Quadtree/Quadtree.h"
#include "../TileMap/TileMap.h"
#include "../EventManager/EventHandler.h"
#include "../EventManager/EventExecutorAware.h"

namespace Framework
{
	class TileMapScene
		:	public SceneBase
		,	public EventHandler
		,	public EventExecutorAware
	{
	public:
		typedef std::unordered_map<ObjectId, GameObject*> ObjectHashTable;
		typedef ObjectHashTable::iterator			 ObjectHashTableIterator;

		TileMapScene();
		~TileMapScene();

	private:
		ObjectHashTable*	m_objectTable;
		Quadtree*			m_quadtree;
		TileMap*			m_tileMap;

		GameObject*			m_playerObject;
		GameObject*			m_cameraObject;
		GameObject*			m_tileMapObject;
		GameObject*			m_npcObject;

		virtual void HandleEvent(Event* pEvent);

		bool LoadObjects();
		void AddObject(ObjectId id, GameObject* obj);
	public:
		bool LoadSceneFromFile(std::string file);
		void SetPlayerObject(GameObject* pPlayerObject) { m_playerObject = pPlayerObject; };
		void SetCameraObject(GameObject* pCameraObject) { m_cameraObject = pCameraObject; };


		void Init();
		void Update();
		void Draw();
		void Pause();
		void Resume();
	};
}

#endif