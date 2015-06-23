#ifndef __TILEMAP_SCENE_H__
#define __TILEMAP_SCENE_H__
#include "../Application/Context.h"
#include "SceneBase.h"
#include "../GameObjects/GameObject.h"
#include "../Quadtree/Quadtree.h"
#include "../TileMap/TileMap.h"
#include "../EventManager/EventHandler.h"
#include "../EventManager/EventExecutorAware.h"
#include "../Utilities/ObjectFactory.h"
#include "../GameObjects/Components/BulletComponent.h"
#include "../Collision/CollisionManager.h"

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
		//std::vector<GameObject*>*				m_updatedObjects;
		std::vector<GameObject*>::iterator		m_objectIter;
		
		GameObject*					m_cameraObject;
		GameObject*					m_tileMapObject;

		Vector3						m_transition;
		void HandleEvent(Event* pEvent);
	public:

		bool LoadSceneFromFile(std::string file);
		void AddUpdateObject(GameObject* pObj);
		void AddUpdateObjects(std::vector<GameObject*>* objects);
		void SetCameraObject(GameObject* pCameraObj);
		//void RemoveUpdateObject(GameObject* pObj);
		void SetTransition(Vector3& vector) { m_transition = vector; }


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
		CollisionManager::GetSingletonPtr()->AddUpdateObject(pObj);
		//m_updatedObjects->push_back(pObj);
		//BulletComponent* pBulletComponent = component_cast<BulletComponent>(pObj);
		//if (pBulletComponent != NULL)
		//{
		//	std::vector<GameObject*>* bullets = pBulletComponent->GetBullets();
		//	assert(bullets);
		//	if (bullets)
		//	{
		//		CollisionManager::GetSingletonPtr()->AddUpdateObjects(bullets);
		//		//m_updatedObjects->insert(m_updatedObjects->begin(), bullets->begin(), bullets->end());
		//	}
		//}
	}

	inline void TileMapScene::AddUpdateObjects(std::vector<GameObject*>* objects)
	{
		CollisionManager::GetSingletonPtr()->AddUpdateObjects(objects);
		/*BulletComponent* pBulletComponent = NULL;
		std::vector<GameObject*>* bullets = NULL;
		for (std::vector<GameObject*>::iterator it = objects->begin(); it != objects->end(); it++)
		{
			AddUpdateObject(*it);
		}*/
	}

	//inline void TileMapScene::RemoveUpdateObject(GameObject* pObj)
	//{
	//	bool find = false;
	//	for (m_objectIter = m_updatedObjects->begin(); m_objectIter != m_updatedObjects->end(); m_objectIter++)
	//	{
	//		if (*m_objectIter == pObj)
	//		{
	//			find = true;
	//			break;
	//		}
	//	}
	//	if (find)
	//		m_updatedObjects->erase(m_objectIter);
	//}
}

#endif