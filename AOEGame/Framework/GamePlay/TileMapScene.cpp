#include "TileMapScene.h"
#include "../Utilities/TmxLoader.h"
#include "../Quadtree/QuadtreeLoader.h"
#include "../GameObjects/Components/CameraComponent.h"
#include "../Collision/CollisionManager.h"
#include "../EventManager/EventManager.h"
#include "../../ContraGameFactory.h"
#include "../Utilities/Console.h"
#include "../Utilities/FPSCounter.h"

namespace Framework
{
	TileMapScene::TileMapScene()
		: EventExecutorAware()
		, m_currentObjects(new std::vector<GameObject*>())
		, m_updatedObjects(new std::vector<GameObject*>())
		, m_tileMap(NULL)
		, m_tileMapObject(NULL)
		, m_cameraObject(NULL)
		
	{
	}

	TileMapScene::~TileMapScene()
	{
		m_currentObjects->clear();
		m_currentObjects->shrink_to_fit();
		SAFE_DELETE(m_currentObjects);
		SAFE_DELETE(m_tileMapObject);
		SAFE_DELETE(m_cameraObject);
		//Remove object hashtable
	}

	bool TileMapScene::LoadSceneFromFile(std::string file)
	{
		TmxLoader *tmxLoader = new TmxLoader(file);
		bool res = tmxLoader->Load();
		if (!res)
		{
			throw new GameError(GameErrorNS::FATAL_ERROR, "Cannot load map!");
		}
		
		m_tileMap = tmxLoader->GetTileMap();
		m_tileMap->Prepare();

		CollisionManager::GetSingletonPtr()->AddCollisionBinFromTileMap(m_tileMap, this);

		delete tmxLoader;
		return true;
	}


	void TileMapScene::Init()
	{
		//!IMPORTANT REQUIRE
		Framework::SetActiveExecutor(this);
		Framework::AttachEvent(Events::SCE_PRE_UPDATE_EVENT, *this);
		Framework::AttachEvent(Events::SCE_UPDATE_EVENT, *this);
		Framework::AttachEvent(Events::SCE_POST_UPDATE_EVENT, *this);
		Framework::AttachEvent(Events::SCE_PRE_RENDER_EVENT, *this);
		Framework::AttachEvent(Events::SCE_RENDER_EVENT, *this);


		if (m_cameraObject != NULL)
		{
			m_cameraObject->InitializeComponents();
		}

		for (m_objectIter = m_updatedObjects->begin(); m_objectIter != m_updatedObjects->end(); m_objectIter++)
		{
			GameObject* obj = *m_objectIter;
			if (obj)
			obj->InitializeComponents();
		}

		m_tileMap->Init();

		m_tileMapObject = ContraGameFactory::GetSingletonPtr()->GetTileMapObject(m_tileMap);
		m_tileMapObject->InitializeComponents();



		CameraComponent* pCameraComponent = component_cast<CameraComponent>(m_cameraObject);
		assert(pCameraComponent);
		if (pCameraComponent)
		{
			pCameraComponent->SetBound(m_tileMap->GetBound());
		}
		
	}

	void TileMapScene::HandleEvent(Event* pEvent)
	{
		if (pEvent->GetID() == Events::SCE_PRE_UPDATE_EVENT)
		{
			FPSCounter::GetSingletonPtr()->StartCounterTest1();
			
			CollisionManager::GetSingletonPtr()->SetExecutor(this);
			//std::vector<GameObject*>*	tempObjectList = 
				
			CollisionManager::GetSingletonPtr()->GetCurrentObjectList(m_currentObjects);
			//m_currentObjects->swap(*tempObjectList);
			
			Console::GetSingletonPtr()->print("Object count (%d)", m_currentObjects->size());
			Console::GetSingletonPtr()->print("Query Range Time (%lf)", FPSCounter::GetSingletonPtr()->GetCounterTest1());
		}
		else if (pEvent->GetID() == Events::SCE_POST_UPDATE_EVENT)
		{
			Framework::BroadcastComponentEvent(Events::COM_POST_UPDATE_EVENT, m_currentObjects, NULL);
			Framework::BroadcastComponentEvent(Events::COM_POST_UPDATE_EVENT, m_updatedObjects, NULL);
			//Framework::SendComponentEvent(Events::COM_POST_UPDATE_EVENT, m_playerObject, NULL);
			//Framework::SendComponentEvent(Events::COM_POST_UPDATE_EVENT, m_npcObject, NULL);



			/*********************************************************************************************************************/
			/*										Check collision																 */
			/*																													 */
			/*********************************************************************************************************************/
			//CollisionManager::GetSingletonPtr()->TestAgainstBin(m_playerObject);
			//CollisionManager::GetSingletonPtr()->TestAgainstBin(m_npcObject);
			/*CollisionManager::GetSingletonPtr()->TestAgainstBin(m_updatedObjects);*/
			CollisionManager::GetSingletonPtr()->TestAgainstBin(m_updatedObjects);
		}
		else if (pEvent->GetID() == Events::SCE_UPDATE_EVENT)
		{
			Framework::BroadcastComponentEvent(Events::COM_UPDATE_EVENT, m_currentObjects, NULL);
			Framework::BroadcastComponentEvent(Events::COM_UPDATE_EVENT, m_updatedObjects, NULL);
			//Framework::SendComponentEvent(Events::COM_UPDATE_EVENT, m_playerObject, NULL);
			//Framework::SendComponentEvent(Events::COM_UPDATE_EVENT, m_npcObject, NULL);
		}
		else if (pEvent->GetID() == Events::SCE_PRE_RENDER_EVENT)
		{

		}
		else if (pEvent->GetID() == Events::SCE_RENDER_EVENT)
		{
			Framework::BroadcastComponentEvent(Events::COM_RENDER_EVENT, m_currentObjects, NULL);
			Framework::BroadcastComponentEvent(Events::COM_RENDER_EVENT, m_updatedObjects, NULL);
			//Framework::SendComponentEvent(Events::COM_RENDER_EVENT, m_playerObject, NULL);
			//Framework::SendComponentEvent(Events::COM_RENDER_EVENT, m_npcObject, NULL);
		}
	}

	void TileMapScene::Update()
	{
		//!IMPORTANT REQUIRE
		Framework::SetActiveExecutor(this);
		Framework::SendEvent(Events::SCE_PRE_UPDATE_EVENT);
		Framework::SendEvent(Events::SCE_UPDATE_EVENT); 
		Framework::SendEvent(Events::SCE_POST_UPDATE_EVENT);
	}

	void TileMapScene::Draw()
	{
		Framework::SendEvent(Events::SCE_PRE_RENDER_EVENT);
		Framework::SendEvent(Events::SCE_RENDER_EVENT);
	}

	void TileMapScene::Pause()
	{

	}

	void TileMapScene::Resume()
	{

	}

	void TileMapScene::Entered()
	{

	}

	void TileMapScene::Leaving()
	{

	}

	void TileMapScene::Obscuring()
	{

	}

	void TileMapScene::Revealed()
	{

	}
}