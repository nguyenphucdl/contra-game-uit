#include "CommonGameFactory.h"
#include "GameResources.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\GameObjects\Components\CollisionComponent.h"
#include "Framework\GameObjects\Components\BulletComponent.h"
#include "Framework\Collision\CollisionManager.h"
#include "Framework\GameObjects\Components\LifeTimeComponent.h"
#include "Framework\GameObjects\Components\TileMapComponent.h"
#include "Framework\GameObjects\Components\CameraComponent.h"
#include "Framework\GameObjects\Actions\Animation.h"
#include "Framework\GameObjects\Components\HealthBarComponent.h"
#include "PlayerMovementComponent.h"
#include "Framework\Utilities\Utils.h"

#include "MovementComponent.h"

using namespace Framework;

void CommonGameFactory::_createPlayerObject(Framework::GameObject* owner, void* data)
{
	owner->SetTag("Player Object");
	AnimCache* propLoader = new AnimCache("Resources\\Texture\\Rockman\\rockman.plist");
	propLoader->Load();

	AnimCache* propLoader2 = new AnimCache("Resources\\Texture\\Rockman\\rockman2.plist");
	propLoader2->Load();

	owner->AddComponent<SpriteComponent>();
	SpriteComponent* pSpriteComponent = component_cast<SpriteComponent>(owner);
	if (pSpriteComponent)
	{
		Animation* moveLeftAnim = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 3);
		Animation* moveRightAnim = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 3, 3);
		Animation* stationaryLeft = Animation::CreateAnimation(GameResources::ROCKMAN_STATIONARY, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);
		Animation* stationaryRight = Animation::CreateAnimation(GameResources::ROCKMAN_STATIONARY, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 3, 1);
		Animation* moveLeftFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 1, 3);
		Animation* moveRightFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 5, 3);
		Animation* stationLeftFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);
		Animation* stationRightFiring = Animation::CreateAnimation(GameResources::ROCKMAN_RUNNING_FIRING, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 7, 1);
		Animation* jumpLeftAnim = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);
		Animation* jumpRightAnim = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 5, 1);
		Animation* jumpLeftFiring = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 1, 1);
		Animation* jumpRightFiring = Animation::CreateAnimation(GameResources::ROCKMAN_JUMPING, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 4, 1);
		Animation* climbingLeftAnim = Animation::CreateAnimation(GameResources::ROCKMAN_CLIMBING, propLoader2, GameResources::CONST_SPRITE_ANIMATION_TIME, 2, 1);
		Animation* climbingRightAnim = Animation::CreateAnimation(GameResources::ROCKMAN_CLIMBING, propLoader2, GameResources::CONST_SPRITE_ANIMATION_TIME, 3, 1);
		Animation* climbingAnim = Animation::CreateAnimation(GameResources::ROCKMAN_CLIMBING, propLoader2, GameResources::CONST_CLIMBING_ANIMATION_TIME, 2, 2);

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
		pSpriteComponent->RegisterState(SpriteStates::CLIMB, SpriteDirections::LEFT, climbingLeftAnim);
		pSpriteComponent->RegisterState(SpriteStates::CLIMB, SpriteDirections::RIGHT, climbingRightAnim);
		pSpriteComponent->RegisterState(SpriteStates::CLIMBING, SpriteDirections::LEFT, climbingAnim);
		pSpriteComponent->RegisterState(SpriteStates::CLIMBING, SpriteDirections::RIGHT, climbingAnim);

		pSpriteComponent->SetUseBounds(true);
		pSpriteComponent->SetBoundMin(Vector3(0.0f, 0.0f, 1.0f));
		pSpriteComponent->SetBoundMax(Vector3(45.0f, 45.0f, 1.0f));
		pSpriteComponent->SetDefaultState(SpriteStates::STATIONARY);
		pSpriteComponent->SetDefaultDirection(SpriteDirections::LEFT);
		pSpriteComponent->SetZIndex(RenderableIndex::OBJECT_INDEX_HIGH);
	}


	owner->AddComponent<PlayerMovementComponent>();
	PlayerMovementComponent* pPlayerTransformComponent = component_cast<PlayerMovementComponent>(owner);
	if (pPlayerTransformComponent)
	{
		pPlayerTransformComponent->AttachRenderableTransform(pSpriteComponent);

		TileMap* tileMap = static_cast<TileMap*>(data);
		Vector3 position = Vector3(300, 200, 0);
		if (tileMap != NULL)
		{
			position.Set(tileMap->GetPlayerPosition());
		}
		//SET player origin
		pPlayerTransformComponent->SetTranslation(&position);
		pPlayerTransformComponent->SetHealth(200);
	}
	owner->AddComponent<HealthBarComponent>();
	HealthBarComponent* pHealthBarComponent = component_cast<HealthBarComponent>(owner);
	if (pHealthBarComponent)
	{
		AnimCache* healBarProp = new AnimCache("Resources\\Texture\\Rockman\\health-bar.plist");
		healBarProp->Load();
		Animation* healthBarForeground = Animation::CreateAnimation(GameResources::ROCKMAN_HEALTH_BAR, healBarProp, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);
		Animation* healthBarBackground = Animation::CreateAnimation(GameResources::HEALTH__BACKGROUND_BAR, healBarProp, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);

		
		pHealthBarComponent->GetBarSpriteComponent().RegisterState(SpriteStates::STATIONARY, healthBarBackground);
		pHealthBarComponent->GetHealthSpriteComponent().RegisterState(SpriteStates::STATIONARY, healthBarForeground);
		pHealthBarComponent->AttachHealthFunc(pPlayerTransformComponent);
		Vector3 barPosition = Vector3(50, 450, 0);
		pHealthBarComponent->GetBarSpriteComponent().SetTranslation(barPosition);
		pHealthBarComponent->GetHealthSpriteComponent().SetTranslation(barPosition);

		TextureRegion* texHealthRegion = healthBarForeground->Current();
		TextureRegion* texBarRegion = healthBarBackground->Current();
		int healthBarHeight = texHealthRegion->GetTextureHeight();
		pHealthBarComponent->SetHeight(healthBarHeight);
		pHealthBarComponent->SetOriginHealthRegion(texHealthRegion->GetRect());
		pHealthBarComponent->SetOriginBarRegion(texBarRegion->GetRect());

	}
	owner->AddComponent<CollisionComponent>();
	CollisionComponent* pCollisionComponent = component_cast<CollisionComponent>(owner);
	if (pCollisionComponent)
	{
		pCollisionComponent->AttachRenderable(&pSpriteComponent->GetRenderable());
		pCollisionComponent->AddEventListener(pPlayerTransformComponent);
		pCollisionComponent->SetActive(true);
	}
	owner->AddComponent<BulletComponent>();
	BulletComponent* pPlayerBulletComponent = component_cast<BulletComponent>(owner);

	if (pPlayerBulletComponent)
	{
		pPlayerBulletComponent->SetVelocity(GameResources::CONST_BULLET_VELOCITY_X, GameResources::CONST_BULLET_VELOCITY_Y);
		pPlayerBulletComponent->SetDelay(GameResources::CONST_BULLET_DELAY_TIME);
		pPlayerBulletComponent->SetSpawnOffset(30.0f, 8.0f);

		int rockman_bullet_counts = 10;
		for (int i = 0; i < rockman_bullet_counts; i++)
		{
			GameObject* rockmanBullet = new GameObject(Utils::getNextId());
			rockmanBullet->SetTag("Rockman Bullet");
			rockmanBullet->AddComponent<SpriteComponent>();
			SpriteComponent* pRockmanBulletComponent = component_cast<SpriteComponent>(rockmanBullet);
			if (pRockmanBulletComponent)
			{
				Animation* bulletFiring = Animation::CreateAnimation(GameResources::ROCKMAN_BULLET_FIRING, propLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);

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
			}
			rockmanBullet->AddComponent<TransformComponent>();
			TransformComponent *pRockmanBulletTransformComponent = component_cast<TransformComponent>(rockmanBullet);
			if (pRockmanBulletTransformComponent)
			{
				pRockmanBulletTransformComponent->AttachRenderableTransform(pRockmanBulletComponent);
				Vector3 position = Vector3(300 + i * 50, 200, 0);
				pRockmanBulletTransformComponent->SetTranslation(&position);
			}
			rockmanBullet->AddComponent<CollisionComponent>();
			CollisionComponent* pBulletCollisionComponent = component_cast<CollisionComponent>(rockmanBullet);
			if (pBulletCollisionComponent)
			{
				pBulletCollisionComponent->AttachRenderable(&pRockmanBulletComponent->GetRenderable());
				pBulletCollisionComponent->AddEventListener(pPlayerBulletComponent);
				pBulletCollisionComponent->SetActive(true);
			}

			rockmanBullet->AddComponent<LifeTimeComponent>();
			LifeTimeComponent* pLifeTimeComponent = component_cast<LifeTimeComponent>(rockmanBullet);
			if (pLifeTimeComponent)
			{
				pLifeTimeComponent->SetLifeTime(GameResources::CONST_BULLET_LIFETIME);
			}

			pPlayerBulletComponent->AddBullet(rockmanBullet);
		}//end for rockman_bullet_counts
	}//end if pBulletComponent
}

void CommonGameFactory::_createTileMapObject(Framework::GameObject* owner, Framework::TileMap* pTileMap)
{
	owner->AddComponent<TileMapComponent>();
	TileMapComponent* pTileMapComponent = component_cast<TileMapComponent>(owner);
	if (pTileMapComponent)
	{
		pTileMapComponent->SetTileMap(pTileMap);
		//pTileMapComponent->SetOrigin(0, 480, 1);
		Transform trans = Transform();
		trans.SetTranslation(Vector3(0, 480, 1));
		pTileMapComponent->SetTransform(trans);
		pTileMapComponent->SetTag("TileMap");
		pTileMapComponent->SetDebug(false);


		Vector3 mapViewportOrigin = Vector3(0.0f, 0.0f, 1.0f);


		switch (pTileMap->GetViewportType())
		{
		case ViewportTypes::TOP_LEFT:
			mapViewportOrigin.m_y = pTileMap->GetBound().bottom - Renderer::GetSingletonPtr()->GetHeight();
			break;
		case ViewportTypes::TOP_RIGHT:
			mapViewportOrigin.m_x = pTileMap->GetBound().right - Renderer::GetSingletonPtr()->GetCamera().GetViewPortWidth();
			break;
		case ViewportTypes::BOTTOM_LEFT:
			mapViewportOrigin.m_y = pTileMap->GetBound().bottom - Renderer::GetSingletonPtr()->GetHeight();
			break;
		case ViewportTypes::BOTTOM_RIGHT:
			mapViewportOrigin.m_x = pTileMap->GetBound().right - Renderer::GetSingletonPtr()->GetCamera().GetViewPortWidth();
			mapViewportOrigin.m_y = pTileMap->GetBound().bottom - Renderer::GetSingletonPtr()->GetHeight();
			break;
		default:
			break;
		}
		pTileMapComponent->SetMapOrigin(mapViewportOrigin);
	}
}

void CommonGameFactory::_createCameraObject(Framework::GameObject* owner, Framework::GameObject* pAttachObj)
{
	owner->AddComponent<CameraComponent>();
	CameraComponent *pCameraComponent = component_cast<CameraComponent>(owner);
	if (pCameraComponent)
	{
		pCameraComponent->SetViewportOrigin(0, 1760);
		RECT default;
		default.left = 0;
		default.right = 640;
		default.top = 0;
		default.bottom = 480;
		pCameraComponent->SetBound(default);
		pCameraComponent->AttachObject(pAttachObj);
	}
}











//Framework::GameObject* CommonGameFactory::GetTileMapObjectMap1Scene2(Framework::TileMap* tileMap)
//{
//	GameObject* tileMapObject = new GameObject(Utils::getNextId());
//	tileMapObject->AddComponent<TileMapComponent>();
//	TileMapComponent* pTileMapComponent = component_cast<TileMapComponent>(tileMapObject);
//	if (pTileMapComponent)
//	{
//		pTileMapComponent->SetTileMap(tileMap);
//		//pTileMapComponent->SetOrigin(0, 480, 1);
//		Transform trans = Transform();
//		trans.SetTranslation(Vector3(0, 480, 1));
//		pTileMapComponent->SetTransform(trans);
//		pTileMapComponent->SetTag("TileMap");
//		pTileMapComponent->SetDebug(false);
//		pTileMapComponent->SetMapOrigin(Vector3(0.0f, tileMap->GetBound().bottom - Renderer::GetSingletonPtr()->GetCamera().GetViewPortHeight(), 1.0f));
//	}
//	return tileMapObject;
//}

//Framework::GameObject* CommonGameFactory::GetNpcTestObject()
//{
//	AnimCache* npcPropLoader = new AnimCache("Resources\\Texture\\Map1\\npc.plist");
//	npcPropLoader->Load();
//
//	GameObject* m_npc1 = new GameObject(Utils::getNextId());
//	m_npc1->AddComponent<SpriteComponent>();
//	SpriteComponent* pNpc1SpriteComponent = component_cast<SpriteComponent>(m_npc1);
//	if (pNpc1SpriteComponent)
//	{
//		Animation* jumpAnimNpc = Animation::CreateAnimation(GameResources::MAP1_NPC_LITTLEPOLYGOT, npcPropLoader, 180.0f, 1, 1);
//		Animation* stationaryAnimNpc = Animation::CreateAnimation(GameResources::MAP1_NPC_LITTLEPOLYGOT, npcPropLoader, 180.0f, 0, 1);
//
//		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::LEFT, stationaryAnimNpc);
//		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::RIGHT, stationaryAnimNpc);
//		pNpc1SpriteComponent->RegisterState(SpriteStates::JUMP, SpriteDirections::LEFT, jumpAnimNpc);
//		pNpc1SpriteComponent->RegisterState(SpriteStates::JUMP, SpriteDirections::RIGHT, jumpAnimNpc);
//		pNpc1SpriteComponent->SetTag("npc");
//		pNpc1SpriteComponent->SetUseBounds(true);
//		pNpc1SpriteComponent->SetRenderTransform(true);
//		pNpc1SpriteComponent->SetBoundMin(Vector3(0.0f, 0.0f, 1.0f));
//		pNpc1SpriteComponent->SetBoundMax(Vector3(30.0f, 30.0f, 1.0f));
//		pNpc1SpriteComponent->SetDefaultState(SpriteStates::STATIONARY);
//		pNpc1SpriteComponent->SetDefaultDirection(SpriteDirections::LEFT);
//		pNpc1SpriteComponent->SetZIndex(RenderableIndex::OBJECT_INDEX_HIGH);
//		////pNpc1SpriteComponent->Initialize();
//	}
//	m_npc1->AddComponent<MovementComponent>();
//	MovementComponent* pNpcMovementComponent = component_cast<MovementComponent>(m_npc1);
//	if (pNpcMovementComponent)
//	{
//		pNpcMovementComponent->AttachRenderableTransform(pNpc1SpriteComponent);
//		Vector3 position = Vector3(350, 140, 0);
//		//Vector3 translation = Vector3(0, 0, 0);
//		pNpcMovementComponent->SetTranslation(&position);
//		////pNpcMovementComponent->Initialize();
//	}
//	m_npc1->AddComponent<CollisionComponent>();
//	CollisionComponent* pNpcCollisionComponent = component_cast<CollisionComponent>(m_npc1);
//	if (pNpcCollisionComponent)
//	{
//		pNpcCollisionComponent->AttachRenderable(&pNpc1SpriteComponent->GetRenderable());
//		//pNpcCollisionComponent->Initialize();
//		
//		pNpcCollisionComponent->AddEventListener(pNpcMovementComponent);
//		//CollisionManager::GetSingletonPtr()->AddObjectToBin(0, pNpcCollisionComponent);		
//	}
//	return m_npc1;
//}