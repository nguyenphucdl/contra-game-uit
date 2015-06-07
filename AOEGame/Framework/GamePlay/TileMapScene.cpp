#include "TileMapScene.h"
#include "../Utilities/TmxLoader.h"
#include "../Quadtree/QuadtreeLoader.h"
#include "../GameObjects/Components/CameraComponent.h"
#include "../Collision/CollisionManager.h"
#include "../EventManager/EventManager.h"
#include "../../ContraGameFactory.h"

namespace Framework
{
	TileMapScene::TileMapScene()
		: EventExecutorAware(ExecutorIDs::SceTileMap)
		, m_currentObjects(new std::vector<GameObject*>())
	{
	}

	TileMapScene::~TileMapScene()
	{
		m_currentObjects->clear();
		//Remove collision bin in collision manager
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

		m_playerObject = ContraGameFactory::GetSingletonPtr()->GetPlayerObject();
		m_cameraObject = ContraGameFactory::GetSingletonPtr()->GetCameraObject(m_playerObject);

		CollisionManager::GetSingletonPtr()->AddCollisionBinFromTileMap(m_tileMap, this);
		return true;
	}

	void TileMapScene::Init()
	{
		//!IMPORTANT REQUIRE
		Framework::SetExecutor(this);
		//Framework::AttachEvent(Events::SCE_PRE_UPDATE_EVENT, *this);
		//Framework::AttachEvent(Events::SCE_UPDATE_EVENT, *this);
		//Framework::AttachEvent(Events::SCE_POST_UPDATE_EVENT, *this);
		//Framework::AttachEvent(Events::SCE_PRE_RENDER_EVENT, *this);
		//Framework::AttachEvent(Events::SCE_RENDER_EVENT, *this);

		m_playerObject->InitializeComponents();
		m_cameraObject->InitializeComponents();

		m_tileMap->Init();

		m_tileMapObject = ContraGameFactory::GetSingletonPtr()->GetTileMapObject(m_tileMap);
		m_tileMapObject->InitializeComponents();



		CameraComponent* pCameraComponent = component_cast<CameraComponent>(m_cameraObject);
		assert(pCameraComponent);
		if (pCameraComponent)
		{
			pCameraComponent->SetBound(m_tileMap->GetBound());
		}
		m_cameraObject->InitializeComponents();

		
	}

	void TileMapScene::HandleEvent(Event* pEvent)
	{
		if (pEvent->GetID() == Events::SCE_PRE_UPDATE_EVENT)
		{
			CollisionManager::GetSingletonPtr()->SetExecutor(this);
			//std::vector<GameObject*>*	tempObjectList = CollisionManager::GetSingletonPtr()->GetCurrentObjectList();
			//m_currentObjects->insert(m_currentObjects->begin(),tempObjectList->begin(), tempObjectList->end());
			//tempObjectList = NULL;

		}
		else if (pEvent->GetID() == Events::SCE_POST_UPDATE_EVENT)
		{
			//Framework::BroadcastEventComponent(Events::COM_POST_UPDATE_EVENT, m_currentObjects, NULL);
			//Framework::SendEventComponent(Events::COM_POST_UPDATE_EVENT, m_playerObject, NULL);


			/*********************************************************************************************************************/
			/*										Check collision																 */
			/*																													 */
			/*********************************************************************************************************************/
			//CollisionManager::GetSingleton().TestAgainstBin(0, m_pNpcCollisionComponent);
			//CollisionManager::GetSingleton().TestAgainstBin(0, m_pPlayerCollisionComponent);
			//CollisionManager::GetSingletonPtr()->TestAgainstBin(m_playerObject);
		}
		else if (pEvent->GetID() == Events::SCE_UPDATE_EVENT)
		{
			//Framework::BroadcastEventComponent(Events::COM_UPDATE_EVENT, m_currentObjects, NULL);
			//Framework::SendEventComponent(Events::COM_UPDATE_EVENT, m_playerObject, NULL);
		}
		else if (pEvent->GetID() == Events::SCE_PRE_RENDER_EVENT)
		{

		}
		else if (pEvent->GetID() == Events::SCE_RENDER_EVENT)
		{
			//Framework::BroadcastEventComponent(Events::COM_RENDER_EVENT, m_currentObjects, NULL);
			//Framework::SendEventComponent(Events::COM_RENDER_EVENT, m_playerObject, NULL);
		}

	}

	void TileMapScene::Update()
	{
		//!IMPORTANT REQUIRE
		Framework::SetExecutor(this);
		Framework::SendEvent(Events::SCE_PRE_UPDATE_EVENT);
		Framework::SendEvent(Events::SCE_UPDATE_EVENT); 
		Framework::SendEvent(Events::SCE_POST_UPDATE_EVENT);
		Framework::SendEvent(Events::SCE_PRE_RENDER_EVENT);
		Framework::SendEvent(Events::SCE_RENDER_EVENT);
	}

	void TileMapScene::Draw()
	{

	}

	void TileMapScene::Pause()
	{

	}

	void TileMapScene::Resume()
	{

	}
}