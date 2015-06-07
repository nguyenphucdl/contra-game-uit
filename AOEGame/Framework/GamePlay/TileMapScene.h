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
		

		TileMapScene();
		~TileMapScene();

	private:
		std::vector<GameObject*>*	m_currentObjects;

		TileMap*					m_tileMap;

		GameObject*					m_playerObject;
		GameObject*					m_cameraObject;
		GameObject*					m_tileMapObject;
		GameObject*					m_npcObject;

		virtual void HandleEvent(Event* pEvent);

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