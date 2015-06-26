#include "MegamanMap1Factory.h"
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
#include "Framework\Utilities\ObjectMapData.h"

#include "MovementComponent.h"


using namespace Framework;

MegamanMap1Factory::MegamanMap1Factory()
{

}

MegamanMap1Factory::~MegamanMap1Factory()
{

}

void MegamanMap1Factory::createObjectType(std::string objectType, Framework::GameObject* owner, void* pData)
{
	int objType = atoi(objectType.c_str());

	switch (objType)
	{
	case GameResources::GameObjectTypes::LITTLE_POGOBOT:
		_createLittlePogobot(owner, pData);
		break;
	case GameResources::GameObjectTypes::PLAYER_OBJECT:
		_createPlayerObject(owner, pData);
		break;
	case GameResources::GameObjectTypes::CAMERA_OBJECT:
		_createCameraObject(owner, static_cast<GameObject*>(pData));
		break;
	case GameResources::GameObjectTypes::TILEMAP_OBJECT:
		_createTileMapObject(owner, static_cast<TileMap*>(pData));
		break;
	default:
		break;
	}

}

void MegamanMap1Factory::_createLittlePogobot(Framework::GameObject* owner, void* pData)
{
	owner->SetTag("LittlePogobot");
	ObjectMapData* objMapData = static_cast<ObjectMapData*>(pData);
	assert(objMapData);
	AnimCache* npcPropLoader = new AnimCache("Resources\\Texture\\Map1\\npc_map1.plist");
	npcPropLoader->Load();
	owner->AddComponent<SpriteComponent>();
	SpriteComponent* pNpc1SpriteComponent = component_cast<SpriteComponent>(owner);
	if (pNpc1SpriteComponent)
	{
		Animation* jumpAnimNpc = Animation::CreateAnimation(GameResources::MAP1_NPC_LITTLEPOLYGOT, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 1, 1);
		Animation* stationaryAnimNpc = Animation::CreateAnimation(GameResources::MAP1_NPC_LITTLEPOLYGOT, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);

		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::LEFT, stationaryAnimNpc);
		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::RIGHT, stationaryAnimNpc);
		pNpc1SpriteComponent->RegisterState(SpriteStates::JUMP, SpriteDirections::LEFT, jumpAnimNpc);
		pNpc1SpriteComponent->RegisterState(SpriteStates::JUMP, SpriteDirections::RIGHT, jumpAnimNpc);
		pNpc1SpriteComponent->SetTag("npc");
		pNpc1SpriteComponent->SetUseBounds(true);
		pNpc1SpriteComponent->SetRenderTransform(true);
		pNpc1SpriteComponent->SetBoundMin(Vector3(0.0f, 0.0f, 1.0f));
		pNpc1SpriteComponent->SetBoundMax(Vector3(35.0f, 35.0f, 1.0f));
		pNpc1SpriteComponent->SetDefaultState(SpriteStates::STATIONARY);
		pNpc1SpriteComponent->SetDefaultDirection(SpriteDirections::LEFT);
		pNpc1SpriteComponent->SetZIndex(RenderableIndex::OBJECT_INDEX_HIGH);
	}
	owner->AddComponent<MovementComponent>();
	MovementComponent* pNpcMovementComponent = component_cast<MovementComponent>(owner);
	if (pNpcMovementComponent)
	{
		pNpcMovementComponent->AttachRenderableTransform(pNpc1SpriteComponent);
		//Vector3 position = Vector3(350, 140, 0);
		Vector3 position = Vector3(objMapData->GetX(), objMapData->GetY(), 0);
		pNpcMovementComponent->SetTranslation(&position);
	}
	owner->AddComponent<CollisionComponent>();
	CollisionComponent* pNpcCollisionComponent = component_cast<CollisionComponent>(owner);
	if (pNpcCollisionComponent)
	{
		pNpcCollisionComponent->AttachRenderable(&pNpc1SpriteComponent->GetRenderable());
		pNpcCollisionComponent->AddEventListener(pNpcMovementComponent);
		pNpcCollisionComponent->SetActive(true);
	}
}

void MegamanMap1Factory::_createAnotherBot(Framework::GameObject* owner, void* pData)
{
	ObjectMapData* objMapData = static_cast<ObjectMapData*>(pData);
	assert(objMapData);
	AnimCache* npcPropLoader = new AnimCache("Resources\\Texture\\Map1\\npc_map1.plist");
	npcPropLoader->Load();

	owner->AddComponent<SpriteComponent>();
	SpriteComponent* pNpc1SpriteComponent = component_cast<SpriteComponent>(owner);
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
		pNpc1SpriteComponent->SetBoundMax(Vector3(35.0f, 35.0f, 1.0f));
		pNpc1SpriteComponent->SetDefaultState(SpriteStates::STATIONARY);
		pNpc1SpriteComponent->SetDefaultDirection(SpriteDirections::LEFT);
		pNpc1SpriteComponent->SetZIndex(RenderableIndex::OBJECT_INDEX_HIGH);
	}
	owner->AddComponent<MovementComponent>();
	MovementComponent* pNpcMovementComponent = component_cast<MovementComponent>(owner);
	if (pNpcMovementComponent)
	{
		pNpcMovementComponent->AttachRenderableTransform(pNpc1SpriteComponent);
		//Vector3 position = Vector3(350, 140, 0);
		Vector3 position = Vector3(objMapData->GetX(), objMapData->GetY(), 0);
		pNpcMovementComponent->SetTranslation(&position);
	}
	owner->AddComponent<CollisionComponent>();
	CollisionComponent* pNpcCollisionComponent = component_cast<CollisionComponent>(owner);
	if (pNpcCollisionComponent)
	{
		pNpcCollisionComponent->AttachRenderable(&pNpc1SpriteComponent->GetRenderable());
		pNpcCollisionComponent->AddEventListener(pNpcMovementComponent);
		pNpcCollisionComponent->SetActive(true);
	}
	AnimCache* propLoader = new AnimCache("Resources\\Texture\\Rockman\\rockman.plist");
	propLoader->Load();
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

		//pPlayerBulletComponent->Initialize();
	}//end if pBulletComponent
}