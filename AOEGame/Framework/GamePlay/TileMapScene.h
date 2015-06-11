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
		TileMap*								m_tileMap;

		std::vector<GameObject*>*				m_currentObjects;
		std::vector<GameObject*>*				m_updatedObjects;
		std::vector<GameObject*>::iterator		m_objectIter;
		
		GameObject*					m_cameraObject;
		GameObject*					m_tileMapObject;

		void HandleEvent(Event* pEvent);
	public:

		bool LoadSceneFromFile(std::string file);
		void AddUpdateObject(GameObject* pObj);
		void SetCameraObject(GameObject* pCameraObj);
		void RemoveUpdateObject(GameObject* pObj);
		

		void Init();
		void Update();
		void Draw();
		void Pause();
		void Resume();

		void Entered();
		void Leaving();
		void Obscuring();
		void Revealed();
	};

	inline void TileMapScene::SetCameraObject(GameObject* pCameraObj)
	{
		m_cameraObject = pCameraObj;
	}

	inline void TileMapScene::AddUpdateObject(GameObject* pObj)
	{
		m_updatedObjects->push_back(pObj);
	}

	inline void TileMapScene::RemoveUpdateObject(GameObject* pObj)
	{
		bool find = false;
		for (m_objectIter = m_updatedObjects->begin(); m_objectIter != m_updatedObjects->end(); m_objectIter++)
		{
			if (*m_objectIter == pObj)
			{
				find = true;
				break;
			}
		}
		if (find)
			m_updatedObjects->erase(m_objectIter);
	}
}

#endif