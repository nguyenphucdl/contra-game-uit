#include "ContraGameFactory.h"
#include "GameResources.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\GameObjects\Components\CollisionComponent.h"
#include "Framework\GameObjects\Components\BulletComponent.h"
#include "Framework\Collision\CollisionManager.h"
#include "Framework\GameObjects\Components\LifeTimeComponent.h"
#include "Framework\GameObjects\Components\TileMapComponent.h"
#include "Framework\GameObjects\Components\CameraComponent.h"
#include "Framework\GameObjects\Actions\Animation.h"
#include "Framework\Utilities\Utils.h"
#include "PlayerMovementComponent.h"
#include "MovementComponent.h"

using namespace Framework;

Framework::GameObject* ContraGameFactory::GetPlayerObject()
{
	AnimCache* propLoader = new AnimCache("Resources\\Texture\\Rockman\\rockman.plist");
	propLoader->Load();

	GameObject* m_playerObject = new GameObject(ObjectIds::PlayerId);
	
	m_playerObject->AddComponent<SpriteComponent>();
	SpriteComponent* pSpriteComponent = component_cast<SpriteComponent>(m_playerObject);
	if (pSpriteComponent)
	{
		Animation* moveLeftAnim = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING, propLoader, 180.0f, 0, 3);
		Animation* moveRightAnim = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING, propLoader, 180.0f, 3, 3);
		Animation* stationaryLeft = Animation::CreateAnimation(GameResources::ROCKMAN_STATIONARY, propLoader, 180.0f, 0, 1);
		Animation* stationaryRight = Animation::CreateAnimation(GameResources::ROCKMAN_STATIONARY, propLoader, 180.0f, 3, 1);
		Animation* moveLeftFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, 180.0f, 1, 3);
		Animation* moveRightFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, 180.0f, 5, 3);
		Animation* stationLeftFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, 180.0f, 0, 1);
		Animation* stationRightFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, 180.0f, 7, 1);
		Animation* jumpLeftAnim = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, 180.0f, 0, 1);
		Animation* jumpRightAnim = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, 180.0f, 5, 1);
		Animation* jumpLeftFiring = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, 180.0f, 1, 1);
		Animation* jumpRightFiring = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, 180.0f, 4, 1);

		pSpriteComponent->SetRenderTransform(true);
		pSpriteComponent->SetDrawCenter(true);
		pSpriteComponent->SetCenter(22.0f, 22.0f);

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
		//pSpriteComponent->Initialize(); Delay Initialize in Scene
	}


	m_playerObject->AddComponent<PlayerMovementComponent>();
	PlayerMovementComponent* pPlayerTransformComponent = component_cast<PlayerMovementComponent>(m_playerObject);
	if (pPlayerTransformComponent)
	{
		pPlayerTransformComponent->AttachRenderableTransform(pSpriteComponent);
		Vector3 position = Vector3(300, 200, 0);
		pPlayerTransformComponent->SetTranslation(&position);
		//pPlayerTransformComponent->Initialize(); Delay Initialize in Scene
	}
	m_playerObject->AddComponent<CollisionComponent>();
	CollisionComponent* pCollisionComponent = component_cast<CollisionComponent>(m_playerObject);
	if (pCollisionComponent)
	{
		pCollisionComponent->AttachRenderable(&pSpriteComponent->GetRenderable());
		//pCollisionComponent->Initialize();
		//Framework::AttachEvent(Events::SCE_COLLISION_EVENT, *pCollisionComponent);
		pCollisionComponent->AddEventListener(pPlayerTransformComponent);
	}
	m_playerObject->AddComponent<BulletComponent>();
	BulletComponent* pPlayerBulletComponent = component_cast<BulletComponent>(m_playerObject);

	if (pPlayerBulletComponent)
	{
		pPlayerBulletComponent->SetVelocity(5000.0f, 0.0f);
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
				//pRockmanBulletComponent->Initialize();
			}
			rockmanBullet->AddComponent<TransformComponent>();
			TransformComponent *pRockmanBulletTransformComponent = component_cast<TransformComponent>(rockmanBullet);
			if (pRockmanBulletTransformComponent)
			{
				pRockmanBulletTransformComponent->AttachRenderableTransform(pRockmanBulletComponent);
				Vector3 position = Vector3(300 + i * 50, 200, 0);
				pRockmanBulletTransformComponent->SetTranslation(&position);
				//pRockmanBulletTransformComponent->Initialize();
			}
			rockmanBullet->AddComponent<CollisionComponent>();
			CollisionComponent* pBulletCollisionComponent = component_cast<CollisionComponent>(rockmanBullet);
			if (pBulletCollisionComponent)
			{
				pBulletCollisionComponent->AttachRenderable(&pRockmanBulletComponent->GetRenderable());
				//pBulletCollisionComponent->Initialize();

				//CollisionManager::GetSingletonPtr()->AddObjectToBin(0, pBulletCollisionComponent);
			}

			rockmanBullet->AddComponent<LifeTimeComponent>();
			LifeTimeComponent* pLifeTimeComponent = component_cast<LifeTimeComponent>(rockmanBullet);
			if (pLifeTimeComponent)
			{
				pLifeTimeComponent->SetLifeTime(0.15f);
				//pLifeTimeComponent->Initialize();
			}

			pPlayerBulletComponent->AddBullet(rockmanBullet);
		}//end for rockman_bullet_counts

		//pPlayerBulletComponent->Initialize();
	}//end if pBulletComponent

	return m_playerObject;
}

Framework::GameObject* ContraGameFactory::GetTileMapObject(TileMap* tileMap)
{
	GameObject* tileMapObject = new GameObject(ObjectIds::TileMapId);
	tileMapObject->AddComponent<TileMapComponent>();
	TileMapComponent* pTileMapComponent = component_cast<TileMapComponent>(tileMapObject);
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
	return tileMapObject;
}

Framework::GameObject* ContraGameFactory::GetNpcTestObject()
{
	AnimCache* npcPropLoader = new AnimCache("Resources\\Texture\\Map1\\npc.plist");
	npcPropLoader->Load();

	GameObject* m_npc1 = new GameObject(Utils::getNextId());
	m_npc1->AddComponent<SpriteComponent>();
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
	m_npc1->AddComponent<MovementComponent>();
	MovementComponent* pNpcMovementComponent = component_cast<MovementComponent>(m_npc1);
	if (pNpcMovementComponent)
	{
		pNpcMovementComponent->AttachRenderableTransform(pNpc1SpriteComponent);
		Vector3 position = Vector3(350, 140, 0);
		//Vector3 translation = Vector3(0, 0, 0);
		pNpcMovementComponent->SetTranslation(&position);
		pNpcMovementComponent->Initialize();
	}
	m_npc1->AddComponent<CollisionComponent>();
	CollisionComponent* pNpcCollisionComponent = component_cast<CollisionComponent>(m_npc1);
	if (pNpcCollisionComponent)
	{
		pNpcCollisionComponent->AttachRenderable(&pNpc1SpriteComponent->GetRenderable());
		//pNpcCollisionComponent->Initialize();
		
		pNpcCollisionComponent->AddEventListener(pNpcMovementComponent);
		//CollisionManager::GetSingletonPtr()->AddObjectToBin(0, pNpcCollisionComponent);		
	}
	return m_npc1;
}

Framework::GameObject* ContraGameFactory::GetCameraObject(GameObject* attachObj)
{
	GameObject* m_cameraObject = new GameObject(ObjectIds::CameraId);
	m_cameraObject->AddComponent<CameraComponent>();
	CameraComponent *pCameraComponent = component_cast<CameraComponent>(m_cameraObject);
	if (pCameraComponent)
	{
		pCameraComponent->SetViewportOrigin(0, 0);
		RECT default;
		default.left = 0;
		default.right = 640;
		default.top = 0;
		default.bottom = 480;
		pCameraComponent->SetBound(default);
		pCameraComponent->AttachObject(attachObj);
		//pCameraComponent->Initialize();
	}
	return m_cameraObject;
}