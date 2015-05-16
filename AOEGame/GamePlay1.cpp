#include "GamePlay1.h"
#include "Framework\Utilities\TmxLoader.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\Utilities\Console.h"
#include "Framework\Utilities\AnimCache.h"
#include "GameResources.h"
#include "Framework\GameObjects\Components\CollisionComponent.h"
#include "Framework\GameObjects\Components\StaticComponent.h"
#include "Framework\Collision\CollisionManager.h"

GamePlay1::GamePlay1(const unsigned int priority)
	: Task(priority, "GamePlay1Task")
{
	
}

GamePlay1::~GamePlay1()
{
}

void GamePlay1::HandleEvent(Event* pEvent)
{
	if (pEvent->GetID() == Events::POST_UPDATE_EVENT)
	{
		Vector3 boundMin = m_pPlayerCollisionComponent->GetMin();
		Vector3 boundMax = m_pPlayerCollisionComponent->GetMax();
		Console::GetSingletonPtr()->print("GamePlay1 Player bound min(%f, %f) max(%f,%f)", boundMin.m_x, boundMin.m_y, boundMax.m_x, boundMax.m_y);

		CollisionManager::GetSingleton().TestAgainstBin(0, m_pPlayerCollisionComponent);
	}

}

bool GamePlay1::Start()
{
	Framework::AttachEvent(Events::POST_UPDATE_EVENT, *this);

	AnimCache* propLoader = new AnimCache("Resources\\Texture\\Rockman\\rockman.plist");
	propLoader->Load();

	//SceneManager
	TmxLoader *tmxLoader = new TmxLoader("Resources\\Maps\\Scence1-Map1\\Scence1-Map1.tmx");
	tmxLoader->Load();

	TileMap* tileMap = tmxLoader->GetTileMap();
	tileMap->Init();


	
	m_objects = tileMap->GetOjects();
	CollisionManager::GetSingletonPtr()->AddCollisionBin();
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
			pThisCollisionComponent->SetMin(Vector3(thisBound.left, thisBound.top, 1.0f));
			pThisCollisionComponent->SetMax(Vector3(thisBound.right, thisBound.bottom, 1.0f));
			Framework::AttachEvent(Events::COLLISION_EVENT, *pThisCollisionComponent);
			CollisionManager::GetSingletonPtr()->AddObjectToBin(0, pThisCollisionComponent);
		}
	}

	
	// TILEMAP OBJECT
	m_tileMapObject.AddComponent<TileMapComponent>();
	TileMapComponent* pTileMapComponent = component_cast<TileMapComponent>(m_tileMapObject);
	if (pTileMapComponent)
	{
		pTileMapComponent->SetTileMap(tileMap);
		pTileMapComponent->SetOrigin(0, 480, 1);
		pTileMapComponent->SetTag("TileMap");
		pTileMapComponent->SetDebug(false);
		//pTileMapComponent->SetRenderTransform(true);
		pTileMapComponent->Initialize();
	}



	//PLAYER OBJECT
	m_playerObject.AddComponent<SpriteComponent>();
	SpriteComponent* pSpriteComponent = component_cast<SpriteComponent>(m_playerObject);
	if (pSpriteComponent)
	{
		Animation* moveLeftAnim = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING, propLoader, 222.0f, 0, 3);
		Animation* moveRightAnim = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING, propLoader, 222.0f, 3, 3);
		Animation* stationaryLeft = Animation::CreateAnimation(GameResources::ROCKMAN_STATIONARY, propLoader, 222.0f, 0, 1);
		Animation* stationaryRight = Animation::CreateAnimation(GameResources::ROCKMAN_STATIONARY, propLoader, 222.0f, 3, 1);
		Animation* moveLeftFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, 222.0f, 1, 3);
		Animation* moveRightFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, 222.0f, 5, 3);
		Animation* stationLeftFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, 222.0f, 0, 1);
		Animation* stationRightFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, 222.0f, 7, 1);
		Animation* jumpLeftAnim = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, 222.0f, 0, 1);
		Animation* jumpRightAnim = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, 222.0f, 5, 1);
		Animation* jumpLeftFiring = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, 222.0f, 1, 1);
		Animation* jumpRightFiring = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, 222.0f, 4, 1);

		Vector3 position = Vector3(300, 130, 0);
		pSpriteComponent->SetRenderTransform(true);
		pSpriteComponent->SetOrigin(position);

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
		pSpriteComponent->Initialize();
	}
	

	m_playerObject.AddComponent<PlayerMovementComponent>();
	PlayerMovementComponent* pPlayerTransformComponent = component_cast<PlayerMovementComponent>(m_playerObject);
	if (pPlayerTransformComponent)
	{
		pPlayerTransformComponent->AttachRenderableTransform(pSpriteComponent);
		Vector3 translation = Vector3(0, 0, 0);
		pPlayerTransformComponent->SetTranslation(&translation);
		pPlayerTransformComponent->Initialize();
	}
	m_playerObject.AddComponent<CollisionComponent>();
	CollisionComponent* pCollisionComponent = component_cast<CollisionComponent>(m_playerObject);
	if (pCollisionComponent)
	{
		pCollisionComponent->AttachRenderable(&pSpriteComponent->GetRenderable());
		pCollisionComponent->Initialize();
		m_pPlayerCollisionComponent = pCollisionComponent;
		Framework::AttachEvent(Events::COLLISION_EVENT, *m_pPlayerCollisionComponent);
		m_pPlayerCollisionComponent->AddEventListener(pPlayerTransformComponent);
	}
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
		pCameraComponent->AttachObject(&m_playerObject);
		pCameraComponent->SetBound(tileMap->GetBound());
		//pCameraComponent->SetViewportOrigin(0, 0);
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
	Framework::SendEvent(Events::UPDATE_EVENT); // need refactor
	Framework::SendEvent(Events::POST_UPDATE_EVENT);
	Framework::SendEvent(Events::RENDER_EVENT);
}

void GamePlay1::OnResume()
{
}

void GamePlay1::Stop()
{
}