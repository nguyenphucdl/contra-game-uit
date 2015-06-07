#include "GamePlay1.h"
#include "Framework\Utilities\TmxLoader.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\Utilities\Console.h"
#include "Framework\Utilities\AnimCache.h"
#include "GameResources.h"
#include "Framework\GameObjects\Components\CollisionComponent.h"
#include "Framework\GameObjects\Components\StaticComponent.h"
#include "Framework\GameObjects\Components\BulletComponent.h"
#include "Framework\GameObjects\Components\LifeTimeComponent.h"
#include "Framework\Collision\CollisionManager.h"
#include "PlayerMovementComponent.h"
#include "Framework\Utilities\Utils.h"
#include "MovementComponent.h"
#include "Framework\Quadtree\QuadtreeLoader.h"


using namespace Framework;
GamePlay1::GamePlay1(const unsigned int priority)
	: Task(priority, "GamePlay1Task")
	, EventExecutorAware(ExecutorIDs::GamePlayId)
	, m_playerObject(ObjectIds::PlayerId)
	, m_npc1(Utils::getNextId())
	, m_cameraObject(ObjectIds::CameraId)
	, m_tileMapObject(ObjectIds::TileMapId)
{
	
}

GamePlay1::~GamePlay1()
{
}

void GamePlay1::HandleEvent(Event* pEvent)
{
	if (pEvent->GetID() == Events::SCE_POST_UPDATE_EVENT)
	{
		Vector3 boundMin = m_pPlayerCollisionComponent->GetAABBMin();
		Vector3 boundMax = m_pPlayerCollisionComponent->GetAABBMax();
		Console::GetSingletonPtr()->print("GamePlay1 Player bound min(%f, %f) max(%f,%f)", boundMin.m_x, boundMin.m_y, boundMax.m_x, boundMax.m_y);

		//CollisionManager::GetSingleton().TestAgainstBin(0, m_pPlayerCollisionComponent);
		//CollisionManager::GetSingleton().TestAgainstBin(0, m_npc1CollisionComponent);
	}

}

bool GamePlay1::Start()
{
	Framework::SetExecutor(this);
	//Framework::RegisterEvent(Events::SCE_UPDATE_EVENT);
	//Framework::RegisterEvent(Events::SCE_POST_UPDATE_EVENT);
	//Framework::RegisterEvent(Events::SCE_PRE_RENDER_EVENT);
	//Framework::RegisterEvent(Events::SCE_RENDER_EVENT);
	//Framework::RegisterEvent(Events::SCE_COLLISION_EVENT);
	//Framework::RegisterEvent(Events::SCE_KEY_DOWN_EVENT);
	//Framework::RegisterEvent(Events::SCE_KEY_UP_EVENT);
	Framework::AttachEvent(Events::SCE_POST_UPDATE_EVENT, *this);

	RECT rect1;

	rect1.left = 100;
	rect1.right = 200;
	rect1.top = 100;
	rect1.bottom = 200;

	RECT rect2;
	rect2.left = 150;
	rect2.right = 250;
	rect2.top = 150;
	rect2.bottom = 250;


	RECT clip = Utils::RectClip(rect1, rect2);

	

	//CollisionManager::GetSingletonPtr()->AddCollisionBin();

	//SceneManager
	TmxLoader *tmxLoader = new TmxLoader("Resources\\Maps\\Scence1-Map1\\Scence1-Map1.tmx");
	tmxLoader->Load();

	TileMap* tileMap = tmxLoader->GetTileMap();
	tileMap->Init();

	float mapScale = tmxLoader->GetScaleRatio();

	QuadtreeLoader* quadtreeLoader = new QuadtreeLoader("Resources\\Maps\\Scence1-Map1\\Scence1-Map1.tmx");
	quadtreeLoader->SetScaleRatio(mapScale);
	quadtreeLoader->Load();

	Quadtree* quadtree = quadtreeLoader->GetQuadTree();

	Rect viewporttest = Rect(0, 0, 640, 480);

	std::vector<int>* updateObjIdList = new std::vector<int>();
	quadtree->QueryRange(viewporttest, updateObjIdList);
	std::sort(updateObjIdList->begin(), updateObjIdList->end());
	std::vector<int>::iterator it = std::unique(updateObjIdList->begin(), updateObjIdList->end());
	updateObjIdList->resize(std::distance(updateObjIdList->begin(), it));

	AnimCache* propLoader = new AnimCache("Resources\\Texture\\Rockman\\rockman.plist");
	propLoader->Load();

	AnimCache* npcPropLoader = new AnimCache("Resources\\Texture\\Map1\\npc.plist");
	npcPropLoader->Load();

	


	
	/*m_objects = tileMap->GetOjects();
	
	for (m_objIt = m_objects->begin(); m_objIt != m_objects->end(); m_objIt++)
	{
		GameObject* t = (GameObject*)(*m_objIt);

		StaticComponent* pThisStaticComponent = component_cast<StaticComponent>(t);
		
		RECT thisBound;
		if (pThisStaticComponent)
		{
			thisBound = pThisStaticComponent->GetBound();
		}
		t->AddComponent<CollisionComponent>();
		CollisionComponent* pThisCollisionComponent = component_cast<CollisionComponent>(t);
		if (pThisCollisionComponent)
		{
			pThisCollisionComponent->SetMin(Vector3(thisBound.left, thisBound.bottom, 1.0f));
			pThisCollisionComponent->SetMax(Vector3(thisBound.right, thisBound.top, 1.0f));
			Framework::AttachEvent(Events::COLLISION_EVENT, *pThisCollisionComponent);
			CollisionManager::GetSingletonPtr()->AddObjectToBin(0, pThisCollisionComponent);
		}
	}*/

	
	// TILEMAP OBJECT
	m_tileMapObject.AddComponent<TileMapComponent>();
	TileMapComponent* pTileMapComponent = component_cast<TileMapComponent>(m_tileMapObject);
	if (pTileMapComponent)
	{
		pTileMapComponent->SetTileMap(tileMap);
		//pTileMapComponent->SetOrigin(0, 480, 1);
		Transform trans = Transform();
		trans.SetTranslation(Vector3(0, 480, 1));
		pTileMapComponent->SetTransform(trans);
		pTileMapComponent->SetTag("TileMap");
		pTileMapComponent->SetDebug(false);
		//pTileMapComponent->SetRenderTransform(true);
		pTileMapComponent->Initialize();
	}

	m_npc1 =  GameObject(Utils::getNextId());
	m_npc1.AddComponent<SpriteComponent>();
	SpriteComponent* pNpc1SpriteComponent = component_cast<SpriteComponent>(m_npc1);
	if (pNpc1SpriteComponent)
	{
		Animation* jumpAnimNpc = Animation::CreateAnimation(GameResources::MAP1_NPC_LITTLEPOLYGOT, npcPropLoader, 180.0f, 1, 1);
		Animation* stationaryAnimNpc = Animation::CreateAnimation(GameResources::MAP1_NPC_LITTLEPOLYGOT, npcPropLoader, 180.0f, 0, 1);

		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::LEFT, stationaryAnimNpc);
		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::RIGHT, stationaryAnimNpc);
		pNpc1SpriteComponent->RegisterState(SpriteStates::JUMP, SpriteDirections::LEFT, jumpAnimNpc);
		pNpc1SpriteComponent->RegisterState(SpriteStates::JUMP, SpriteDirections::RIGHT, jumpAnimNpc);
		pNpc1SpriteComponent->SetTag("npc");
		pNpc1SpriteComponent->SetUseBounds(true);
		pNpc1SpriteComponent->SetRenderTransform(true);
		pNpc1SpriteComponent->SetBoundMin(Vector3(0.0f, 0.0f, 1.0f));
		pNpc1SpriteComponent->SetBoundMax(Vector3(30.0f, 30.0f, 1.0f));
		pNpc1SpriteComponent->SetDefaultState(SpriteStates::STATIONARY);
		pNpc1SpriteComponent->SetDefaultDirection(SpriteDirections::LEFT);
		pNpc1SpriteComponent->SetZIndex(RenderableIndex::OBJECT_INDEX_HIGH);
		pNpc1SpriteComponent->Initialize();
	}
	m_npc1.AddComponent<MovementComponent>();
	MovementComponent* pNpcMovementComponent = component_cast<MovementComponent>(m_npc1);
	if (pNpcMovementComponent)
	{
		pNpcMovementComponent->AttachRenderableTransform(pNpc1SpriteComponent);
		Vector3 position = Vector3(350, 140, 0);
		//Vector3 translation = Vector3(0, 0, 0);
		pNpcMovementComponent->SetTranslation(&position);
		pNpcMovementComponent->Initialize();
	}
	m_npc1.AddComponent<CollisionComponent>();
	CollisionComponent* pNpcCollisionComponent = component_cast<CollisionComponent>(m_npc1);
	if (pNpcCollisionComponent)
	{
		pNpcCollisionComponent->AttachRenderable(&pNpc1SpriteComponent->GetRenderable());
		pNpcCollisionComponent->Initialize();		
		Framework::AttachEvent(Events::SCE_COLLISION_EVENT, *pNpcCollisionComponent);
		pNpcCollisionComponent->AddEventListener(pNpcMovementComponent);
		//CollisionManager::GetSingletonPtr()->AddObjectToBin(0, pNpcCollisionComponent);
		m_npc1CollisionComponent = pNpcCollisionComponent;
	}

	//PLAYER OBJECT
	m_playerObject.AddComponent<SpriteComponent>();
	SpriteComponent* pSpriteComponent = component_cast<SpriteComponent>(m_playerObject);
	if (pSpriteComponent)
	{
		Animation* moveLeftAnim = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING, propLoader, 100.0f, 0, 3);
		Animation* moveRightAnim = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING, propLoader, 100.0f, 3, 3);
		Animation* stationaryLeft = Animation::CreateAnimation(GameResources::ROCKMAN_STATIONARY, propLoader, 100.0f, 0, 1);
		Animation* stationaryRight = Animation::CreateAnimation(GameResources::ROCKMAN_STATIONARY, propLoader, 100.0f, 3, 1);
		Animation* moveLeftFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, 100.0f, 1, 3);
		Animation* moveRightFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, 100.0f, 5, 3);
		Animation* stationLeftFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, 100.0f, 0, 1);
		Animation* stationRightFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, 100.0f, 7, 1);
		Animation* jumpLeftAnim = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, 100.0f, 0, 1);
		Animation* jumpRightAnim = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, 100.0f, 5, 1);
		Animation* jumpLeftFiring = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, 100.0f, 1, 1);
		Animation* jumpRightFiring = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, 100.0f, 4, 1);

		//Vector3 position = Vector3(300, 130, 0);
		pSpriteComponent->SetRenderTransform(true);
		pSpriteComponent->SetDrawCenter(true);
		pSpriteComponent->SetCenter(22.0f, 22.0f);
		//pSpriteComponent->SetOrigin(position);
		//Transform trans = Transform();
		//trans.SetTranslation(position);
		//pSpriteComponent->SetTransform(trans);

		pSpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::LEFT, stationaryLeft);
		pSpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::RIGHT, stationaryRight);
		pSpriteComponent->RegisterState(SpriteStates::STATIONARY_FIRING, SpriteDirections::RIGHT, stationRightFiring);
		pSpriteComponent->RegisterState(SpriteStates::STATIONARY_FIRING, SpriteDirections::LEFT, stationLeftFiring);
		pSpriteComponent->RegisterState(SpriteStates::MOVE, SpriteDirections::LEFT, moveLeftAnim);
		pSpriteComponent->RegisterState(SpriteStates::MOVE, SpriteDirections::RIGHT, moveRightAnim);
		pSpriteComponent->RegisterState(SpriteStates::MOVE_FIRING, SpriteDirections::RIGHT, moveRightFiring);
		pSpriteComponent->RegisterState(SpriteStates::MOVE_FIRING, SpriteDirections::LEFT, moveLeftFiring);
		pSpriteComponent->RegisterState(SpriteStates::JUMP, SpriteDirections::RIGHT, jumpRightAnim);
		pSpriteComponent->RegisterState(SpriteStates::JUMP, SpriteDirections::LEFT, jumpLeftAnim);
		pSpriteComponent->RegisterState(SpriteStates::JUMP_FIRING, SpriteDirections::RIGHT, jumpRightFiring);
		pSpriteComponent->RegisterState(SpriteStates::JUMP_FIRING, SpriteDirections::LEFT, jumpLeftFiring);

		pSpriteComponent->SetUseBounds(true);
		pSpriteComponent->SetBoundMin(Vector3(0.0f, 0.0f, 1.0f));
		pSpriteComponent->SetBoundMax(Vector3(45.0f, 45.0f, 1.0f));
		pSpriteComponent->SetDefaultState(SpriteStates::STATIONARY);
		pSpriteComponent->SetDefaultDirection(SpriteDirections::LEFT);
		pSpriteComponent->SetZIndex(RenderableIndex::OBJECT_INDEX_HIGH);
		pSpriteComponent->Initialize();
	}
	

	m_playerObject.AddComponent<PlayerMovementComponent>();
	PlayerMovementComponent* pPlayerTransformComponent = component_cast<PlayerMovementComponent>(m_playerObject);
	if (pPlayerTransformComponent)
	{
		pPlayerTransformComponent->AttachRenderableTransform(pSpriteComponent);
		Vector3 position = Vector3(300, 200, 0);
		//Vector3 translation = Vector3(0, 0, 0);
		pPlayerTransformComponent->SetTranslation(&position);
		pPlayerTransformComponent->Initialize();
	}
	m_playerObject.AddComponent<CollisionComponent>();
	CollisionComponent* pCollisionComponent = component_cast<CollisionComponent>(m_playerObject);
	if (pCollisionComponent)
	{
		pCollisionComponent->AttachRenderable(&pSpriteComponent->GetRenderable());
		pCollisionComponent->Initialize();
		m_pPlayerCollisionComponent = pCollisionComponent;
		Framework::AttachEvent(Events::SCE_COLLISION_EVENT, *m_pPlayerCollisionComponent);
		m_pPlayerCollisionComponent->AddEventListener(pPlayerTransformComponent);
	}
	m_playerObject.AddComponent<BulletComponent>();
	BulletComponent* pPlayerBulletComponent = component_cast<BulletComponent>(m_playerObject);

	if (pPlayerBulletComponent)
	{
		pPlayerBulletComponent->SetVelocity(300.0f, 0.0f);
		pPlayerBulletComponent->SetSpawnOffset(30.0f, 8.0f);

		int rockman_bullet_counts = 10;
		for (int i = 0; i < rockman_bullet_counts; i++)
		{
			GameObject* rockmanBullet = new GameObject(Utils::getNextId());
			rockmanBullet->AddComponent<SpriteComponent>();
			SpriteComponent* pRockmanBulletComponent = component_cast<SpriteComponent>(rockmanBullet);
			if (pRockmanBulletComponent)
			{
				Animation* bulletFiring = Animation::CreateAnimation(GameResources::ROCKMAN_BULLET_FIRING, propLoader, 222.0f, 0, 1);

				pRockmanBulletComponent->RegisterState(BulletStates::FIRE, SpriteDirections::LEFT, bulletFiring);
				pRockmanBulletComponent->RegisterState(BulletStates::FIRE, SpriteDirections::RIGHT, bulletFiring);
				pRockmanBulletComponent->SetTag("Bullet");
				pRockmanBulletComponent->SetDebug(true);
				pRockmanBulletComponent->SetUseBounds(true);
				pRockmanBulletComponent->SetDebug(false);
				pRockmanBulletComponent->SetBoundMin(Vector3(0.0f, 0.0f, 1.0f));
				pRockmanBulletComponent->SetBoundMax(Vector3(16.0f, 12.0f, 1.0f));
				pRockmanBulletComponent->SetDefaultState(BulletStates::FIRE);
				pRockmanBulletComponent->SetDefaultDirection(SpriteDirections::LEFT);
				pRockmanBulletComponent->Initialize();
			}
			rockmanBullet->AddComponent<TransformComponent>();
			TransformComponent *pRockmanBulletTransformComponent = component_cast<TransformComponent>(rockmanBullet);
			if (pRockmanBulletTransformComponent)
			{
				pRockmanBulletTransformComponent->AttachRenderableTransform(pRockmanBulletComponent);
				Vector3 position = Vector3(300 + i * 50, 200, 0);
				pRockmanBulletTransformComponent->SetTranslation(&position);
				pRockmanBulletTransformComponent->Initialize();
			}
			rockmanBullet->AddComponent<CollisionComponent>();
			CollisionComponent* pBulletCollisionComponent = component_cast<CollisionComponent>(rockmanBullet);
			if (pBulletCollisionComponent)
			{
				pBulletCollisionComponent->AttachRenderable(&pRockmanBulletComponent->GetRenderable());
				pBulletCollisionComponent->Initialize();

				Framework::AttachEvent(Events::SCE_COLLISION_EVENT, *pBulletCollisionComponent);
				//CollisionManager::GetSingletonPtr()->AddObjectToBin(0, pBulletCollisionComponent);
			}
			
			rockmanBullet->AddComponent<LifeTimeComponent>();
			LifeTimeComponent* pLifeTimeComponent = component_cast<LifeTimeComponent>(rockmanBullet);
			if (pLifeTimeComponent)
			{
				pLifeTimeComponent->SetLifeTime(3.0f);
				pLifeTimeComponent->Initialize();
			}


			pPlayerBulletComponent->AddBullet(rockmanBullet);
		}//end for rockman_bullet_counts

		pPlayerBulletComponent->Initialize();
	}//end if pBulletComponent

	

	

	/*m_playerObject.AddComponent<CollisionComponent>();
	CollisionComponent* pPlayerCollisionComponent = component_cast<CollisionComponent>(m_playerObject);
	if (pPlayerCollisionComponent)
	{
		TransformComponent* testTransformComponent = component_cast<TransformComponent>(m_playerObject);
		if (testTransformComponent)
		{
			int k = 3;
		}

	}*/

	TransformComponent* testTransformComponent = component_cast<TransformComponent>(m_playerObject);

	PlayerMovementComponent* testPlayerComponent = dynamic_cast<PlayerMovementComponent*>(testTransformComponent);

	/*m_playerObject.AddComponent<MovementComponent>();
	MovementComponent* pPlayerMovementComponent = component_cast<MovementComponent>(m_playerObject);
	if (pPlayerMovementComponent)
	{
	Vector3 velocity = Vector3(50.0f, 50.0f, 0);
	pPlayerMovementComponent->SetVelocity(velocity);
	pPlayerMovementComponent->Initialize();
	}*/

	// CAMERA OBJECT
	m_cameraObject.AddComponent<CameraComponent>();
	CameraComponent *pCameraComponent = component_cast<CameraComponent>(m_cameraObject);
	if (pCameraComponent)
	{
		pCameraComponent->SetViewportOrigin(0, 0);
		pCameraComponent->SetBound(tileMap->GetBound());
		pCameraComponent->AttachObject(&m_playerObject);
		
		//pCameraComponent->SetViewportTranslate(0, 0);
		pCameraComponent->Initialize();
	}


	Log::printComponentIDs();
	Log::printMapEvents();

	return true;
}

void GamePlay1::OnSuspend()
{
}

void GamePlay1::Update()
{
	//!IMPORTANT REQUIRE
	Framework::SetExecutor(this);
	Framework::SendEvent(Events::SCE_UPDATE_EVENT); // need refactor
	Framework::SendEvent(Events::SCE_POST_UPDATE_EVENT);
	Framework::SendEvent(Events::SCE_PRE_RENDER_EVENT);
	Framework::SendEvent(Events::SCE_RENDER_EVENT);
}

void GamePlay1::OnResume()
{
}

void GamePlay1::Stop()
{
}