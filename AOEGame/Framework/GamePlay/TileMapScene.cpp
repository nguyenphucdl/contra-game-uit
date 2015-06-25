#include "TileMapScene.h"
#include "../Utilities/TmxLoader.h"
#include "../Quadtree/QuadtreeLoader.h"
#include "../GameObjects/Components/CameraComponent.h"
#include "../Collision/CollisionManager.h"
#include "../EventManager/EventManager.h"
#include "../../CommonGameFactory.h"
#include "../Utilities/Console.h"
#include "../Utilities/FPSCounter.h"
#include "../GameObjects/Components/TileMapComponent.h"
#include "../GameObjects/Components/BulletComponent.h"

namespace Framework
{
	TileMapScene::TileMapScene()
		: SceneBase()
		, EventExecutorAware()
		, m_currentObjects(new std::vector<GameObject*>())
		//, m_updatedObjects(new std::vector<GameObject*>())
		, m_tileMap(NULL)
		, m_tileMapObject(NULL)
		, m_cameraObject(NULL)
		, m_transition(0, 0, 1.0f)
		
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
		Framework::SetActiveExecutor(this);
		Utils::resetNextId();
		CollisionManager::GetSingletonPtr()->SetExecutor(this);

		TmxLoader *tmxLoader = new TmxLoader(file);
		tmxLoader->SetObjectFactory(GetObjectFactory());
		bool res = tmxLoader->Load();
		if (!res)
		{
			throw new GameError(GameErrorNS::FATAL_ERROR, "Cannot load map!");
		}
		
		m_tileMap = tmxLoader->GetTileMap();
		m_tileMap->Prepare();		

		CollisionManager::GetSingletonPtr()->AddCollisionBinFromTileMap(m_tileMap, this);

		GameObject* playerObject = new GameObject(Utils::getNextId());
		GetObjectFactory()->createObjectType(std::to_string(SystemObjectTypes::PLAYER_OBJECT), playerObject, m_tileMap);
		AddUpdateObject(playerObject);
		/*BulletComponent* playerBulletComponent = component_cast<BulletComponent>(playerObject);
		if (playerBulletComponent)
		{
			std::vector<GameObject*>* bullets = playerBulletComponent->GetBullets();
			assert(bullets);
			if (bullets)
			{
				AddUpdateObjects(bullets);
			}
		}*/


		m_cameraObject = new GameObject(Utils::getNextId());
		GetObjectFactory()->createObjectType(std::to_string(SystemObjectTypes::CAMERA_OBJECT), m_cameraObject, playerObject);

		m_tileMapObject = new GameObject(Utils::getNextId());
		GetObjectFactory()->createObjectType(std::to_string(SystemObjectTypes::TILEMAP_OBJECT), m_tileMapObject, m_tileMap);
		delete tmxLoader;
		return true;
	}


	void TileMapScene::Init()
	{
		//!IMPORTANT REQUIRE
		Framework::SetActiveExecutor(this);
		CollisionManager::GetSingletonPtr()->SetExecutor(this);

		Framework::AttachEvent(Events::SCE_PRE_UPDATE_EVENT, *this);
		Framework::AttachEvent(Events::SCE_UPDATE_EVENT, *this);
		Framework::AttachEvent(Events::SCE_POST_UPDATE_EVENT, *this);
		Framework::AttachEvent(Events::SCE_PRE_RENDER_EVENT, *this);
		Framework::AttachEvent(Events::SCE_RENDER_EVENT, *this);
		Framework::AttachEvent(Events::SCE_COMPLETE_SCENE_EVENT, *this);
		Framework::AttachEvent(ExecutorIDs::SysInput, Events::SYS_KEY_DOWN_EVENT, *this);

		if (m_cameraObject != NULL)
		{
			m_cameraObject->InitializeComponents();
		}
		
		CollisionManager::GetSingletonPtr()->InitCollisionBin();

		m_tileMap->Init();

		
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
		TileMapScene* that = this;
		Framework::SetActiveExecutor(this);
		CollisionManager::GetSingletonPtr()->SetExecutor(this);

		if (pEvent->GetID() == Events::SCE_PRE_UPDATE_EVENT)
		{
			FPSCounter::GetSingletonPtr()->StartTimeCounter(1);
			CollisionManager::GetSingletonPtr()->GetCurrentObjectList(m_currentObjects);			
			Console::GetSingletonPtr()->print("Object count (%d)", m_currentObjects->size());
			Console::GetSingletonPtr()->print("Query Range Time (%d) (%lf)", 1, FPSCounter::GetSingletonPtr()->GetTimerCounter(1));
		}
		else if (pEvent->GetID() == Events::SCE_POST_UPDATE_EVENT)
		{
			Framework::BroadcastComponentEvent(Events::COM_POST_UPDATE_EVENT, m_currentObjects, NULL);
			//Framework::BroadcastComponentEvent(Events::COM_POST_UPDATE_EVENT, m_updatedObjects, NULL);
			/*********************************************************************************************************************/
			/*										Check collision																 */
			/*																													 */
			/*********************************************************************************************************************/
			
			FPSCounter::GetSingletonPtr()->StartTimeCounter(2);
			FPSCounter::GetSingletonPtr()->StartLoopCounter(2);
			FPSCounter::GetSingletonPtr()->StartLoopCounter(1);
			CollisionManager::GetSingletonPtr()->TestAgainstBin(m_currentObjects);
			Console::GetSingletonPtr()->print("Collision component not active (%d) (%d)", 1, FPSCounter::GetSingletonPtr()->GetLoopCounter(1));
			
			Console::GetSingletonPtr()->print("Test Collision Hit (%d) (%d)", 2, FPSCounter::GetSingletonPtr()->GetLoopCounter(2));
			
			Console::GetSingletonPtr()->print("Query Test Collision Time (%d) (%lf)", 2, FPSCounter::GetSingletonPtr()->GetTimerCounter(2));
		}
		else if (pEvent->GetID() == Events::SCE_UPDATE_EVENT)
		{
			Framework::BroadcastComponentEvent(Events::COM_UPDATE_EVENT, m_currentObjects, NULL);
			//Framework::BroadcastComponentEvent(Events::COM_UPDATE_EVENT, m_updatedObjects, NULL);
		}
		else if (pEvent->GetID() == Events::SCE_PRE_RENDER_EVENT)
		{

		}
		else if (pEvent->GetID() == Events::SCE_RENDER_EVENT)
		{
			Framework::BroadcastComponentEvent(Events::COM_RENDER_EVENT, m_currentObjects, NULL);
			//Framework::BroadcastComponentEvent(Events::COM_RENDER_EVENT, m_updatedObjects, NULL);
		}
		else if (pEvent->GetID() == Events::SCE_COMPLETE_SCENE_EVENT)
		{
			SetScenceState(SceneStates::Completed);
		}
		else if (pEvent->GetID() == Events::SYS_KEY_DOWN_EVENT)
		{
			if ((int)pEvent->GetData() == DIK_H)
			{
				m_transition.m_y += 10.0f;
			}
		}
	}

	void TileMapScene::Update()
	{
		//!IMPORTANT REQUIRE
		Framework::SetActiveExecutor(this);
		Framework::CollisionManager::GetSingletonPtr()->SetExecutor(this);

		RECT viewport = Renderer::GetSingletonPtr()->GetCamera().GetViewPort();
		Console::GetSingletonPtr()->print("Camera Viewport RECT(%d,%d,%d,%d)", viewport.left, viewport.top, viewport.right - viewport.left, viewport.bottom - viewport.top);

		Framework::SendEvent(Events::SCE_PRE_UPDATE_EVENT);
		FPSCounter::GetSingletonPtr()->StartTimeCounter(3);
		Framework::SendEvent(Events::SCE_UPDATE_EVENT); 
		Console::GetSingletonPtr()->print("TileMapScene Update Time (%d) (%lf)", 3, FPSCounter::GetSingletonPtr()->GetTimerCounter(3));
		Framework::SendEvent(Events::SCE_POST_UPDATE_EVENT);
		
	}

	void TileMapScene::Draw()
	{
		Framework::SetActiveExecutor(this);
		D3DXMatrixTransformation2D(&m_transitionMaxtrix, NULL, 0, NULL, 0, 0, &D3DXVECTOR2(m_transition.m_x, m_transition.m_y));
		Renderer::GetSingletonPtr()->SetTransitionMatrix(&m_transitionMaxtrix);
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
		Framework::SendEvent(Events::SCE_ENTERED_EVENT);
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