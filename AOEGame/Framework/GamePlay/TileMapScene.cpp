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
	{

	}

	TileMapScene::~TileMapScene()
	{
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
		m_tileMap->Init();
		m_quadtree = m_tileMap->GetQuadTree();
		m_objectTable = m_tileMap->GetOjectHashTable();
		return true;
	}

	void TileMapScene::Init()
	{
		//!IMPORTANT REQUIRE
		Framework::SetExecutor(this);
		Framework::AttachEvent(Events::SCE_UPDATE_EVENT, *this);
		Framework::AttachEvent(Events::SCE_POST_UPDATE_EVENT, *this);
		Framework::AttachEvent(Events::SCE_PRE_RENDER_EVENT, *this);
		Framework::AttachEvent(Events::SCE_RENDER_EVENT, *this);
		

		

		m_npcObject = ContraGameFactory::GetSingletonPtr()->GetNpcTestObject();
		m_npcObject->InitializeComponents();

		m_tileMapObject = ContraGameFactory::GetSingletonPtr()->GetTileMapObject(m_tileMap);
		m_tileMapObject->InitializeComponents();

		
		m_playerObject->InitializeComponents();
		CameraComponent* pCameraComponent = component_cast<CameraComponent>(m_cameraObject);
		assert(pCameraComponent);
		if (pCameraComponent)
		{
			pCameraComponent->SetBound(m_tileMap->GetBound());
		}
		m_cameraObject->InitializeComponents();
		for (ObjectHashTableIterator it = m_objectTable->begin(); it != m_objectTable->end(); it++)
		{
			assert(it->second);
			GameObject* gameObj = it->second;
			gameObj->InitializeComponents();
		}
		//make_pair(id, gameObj)
		//std::make_pair<ObjectId, GameObject* > mypair(m_playerObject->GetId(), m_playerObject);

		m_objectTable->insert(std::make_pair(m_playerObject->GetId(), m_playerObject));
		m_objectTable->insert(std::make_pair(m_npcObject->GetId(), m_npcObject));
	}

	void TileMapScene::HandleEvent(Event* pEvent)
	{
		if (pEvent->GetID() == Events::SCE_POST_UPDATE_EVENT)
		{
			for (ObjectHashTableIterator it = m_objectTable->begin(); it != m_objectTable->end(); it++)
			{
				GameObject* obj = it->second;
				assert(obj);
				Framework::SendEventComponent(Events::COM_POST_UPDATE_EVENT, obj->GetId(), NULL);
			}


			CollisionComponent* m_pPlayerCollisionComponent = component_cast<CollisionComponent>(m_playerObject);
			CollisionComponent* m_pNpcCollisionComponent = component_cast<CollisionComponent>(m_npcObject);
			assert(m_pPlayerCollisionComponent); assert(m_pNpcCollisionComponent);
			
			//Console::GetSingletonPtr()->print("GamePlay1 Player bound min(%f, %f) max(%f,%f)", boundMin.m_x, boundMin.m_y, boundMax.m_x, boundMax.m_y);

			CollisionManager::GetSingleton().TestAgainstBin(0, m_pNpcCollisionComponent);
			CollisionManager::GetSingleton().TestAgainstBin(0, m_pPlayerCollisionComponent);
		}
		else if (pEvent->GetID() == Events::SCE_UPDATE_EVENT)
		{
			for (ObjectHashTableIterator it = m_objectTable->begin(); it != m_objectTable->end(); it++)
			{
				GameObject* obj = it->second;
				assert(obj);
				Framework::SendEventComponent(Events::COM_UPDATE_EVENT, obj->GetId(), NULL);
			}
		}
		else if (pEvent->GetID() == Events::SCE_PRE_RENDER_EVENT)
		{

		}
		else if (pEvent->GetID() == Events::SCE_RENDER_EVENT)
		{
			
		}

	}

	void TileMapScene::Update()
	{
		//!IMPORTANT REQUIRE
		Framework::SetExecutor(this);
		Framework::SendEvent(Events::SCE_UPDATE_EVENT); // need refactor
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