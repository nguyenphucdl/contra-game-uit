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
#include "Framework\GameObjects\Components\HealthBarComponent.h"

#include "MovementComponent.h"
#include "LittlePolygotMovementComponent.h"


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
	case GameResources::GameObjectTypes::BOSS_BOMBMAN:
		_createBossBombMan(owner, pData);
		break;
	case GameResources::GameObjectTypes::GREEN_ROBOCOP:
		_createGreenRobocop(owner, pData);
		break;
	case GameResources::GameObjectTypes::WALL_SHOOTER:
		_createWallShooter(owner, pData);
		break;
	case GameResources::GameObjectTypes::NAPALM_BOMB:
		_createNapalmBomb(owner, pData);
		break;
	case GameResources::GameObjectTypes::FIVE_STAR_SHOOTER:
		_createFiveStarShooter(owner, pData);
		break;
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
	owner->SetResId(GameResources::LITTLE_POGOBOT);
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
	owner->AddComponent<LittlePolygotMovementComponent>();
	LittlePolygotMovementComponent* pNpcMovementComponent = component_cast<LittlePolygotMovementComponent>(owner);
	if (pNpcMovementComponent)
	{
		pNpcMovementComponent->AttachRenderableTransform(pNpc1SpriteComponent);
		//Vector3 position = Vector3(350, 140, 0);
		pNpcMovementComponent->SetHealth(200);
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
	owner->AddComponent<LittlePolygotMovementComponent>();
	LittlePolygotMovementComponent* pNpcMovementComponent = component_cast<LittlePolygotMovementComponent>(owner);
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

void MegamanMap1Factory::_createNapalmBomb(Framework::GameObject* owner, void* pData)
{
	owner->SetTag("Nalmpal Bomb");
	owner->SetResId(GameResources::NAPALM_BOMB);
	ObjectMapData* objMapData = static_cast<ObjectMapData*>(pData);
	assert(objMapData);
	AnimCache* npcPropLoader = new AnimCache("Resources\\Texture\\Map1\\npc_map1.plist");
	npcPropLoader->Load();
	owner->AddComponent<SpriteComponent>();
	SpriteComponent* pNpc1SpriteComponent = component_cast<SpriteComponent>(owner);
	if (pNpc1SpriteComponent)
	{
		Animation* stationaryAnim = Animation::CreateAnimation(GameResources::MAP1_NPC_NAPALMBOMB, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);
		Animation* bulletAnim = Animation::CreateAnimation(GameResources::MAP1_NPC_NAPALMBOMB, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 1, 1);

		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::LEFT, stationaryAnim);
		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::RIGHT, stationaryAnim);
		pNpc1SpriteComponent->RegisterState(SpriteStates::JUMP, SpriteDirections::LEFT, stationaryAnim);
		pNpc1SpriteComponent->RegisterState(SpriteStates::JUMP, SpriteDirections::RIGHT, stationaryAnim);
		pNpc1SpriteComponent->SetTag("npc");
		pNpc1SpriteComponent->SetUseBounds(true);
		pNpc1SpriteComponent->SetRenderTransform(true);
		pNpc1SpriteComponent->SetBoundMin(Vector3(0.0f, 0.0f, 1.0f));
		pNpc1SpriteComponent->SetBoundMax(Vector3(35.0f, 35.0f, 1.0f));
		pNpc1SpriteComponent->SetDefaultState(SpriteStates::STATIONARY);
		pNpc1SpriteComponent->SetDefaultDirection(SpriteDirections::LEFT);
		pNpc1SpriteComponent->SetZIndex(RenderableIndex::OBJECT_INDEX_HIGH);
	}
	owner->AddComponent<LittlePolygotMovementComponent>();
	LittlePolygotMovementComponent* pNpcMovementComponent = component_cast<LittlePolygotMovementComponent>(owner);
	if (pNpcMovementComponent)
	{
		pNpcMovementComponent->AttachRenderableTransform(pNpc1SpriteComponent);
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

void MegamanMap1Factory::_createFiveStarShooter(Framework::GameObject* owner, void* pData)
{
	owner->SetTag("Five Star Shooter");
	owner->SetResId(GameResources::FIVE_STAR_SHOOTER);
	ObjectMapData* objMapData = static_cast<ObjectMapData*>(pData);
	assert(objMapData);
	AnimCache* npcPropLoader = new AnimCache("Resources\\Texture\\Map1\\npc_map1.plist");
	npcPropLoader->Load();
	owner->AddComponent<SpriteComponent>();
	SpriteComponent* pNpc1SpriteComponent = component_cast<SpriteComponent>(owner);
	if (pNpc1SpriteComponent)
	{
		Animation* stationayryAnim = Animation::CreateAnimation(GameResources::MAP1_FIVESTARSHOOTER, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 4, 1);
		Animation* firingAnim = Animation::CreateAnimation(GameResources::MAP1_FIVESTARSHOOTER, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 1, 3);

		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::LEFT, stationayryAnim);
		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::RIGHT, stationayryAnim);
		pNpc1SpriteComponent->RegisterState(SpriteStates::FIRING, firingAnim);
		pNpc1SpriteComponent->SetTag("npc");
		pNpc1SpriteComponent->SetUseBounds(true);
		pNpc1SpriteComponent->SetRenderTransform(true);
		pNpc1SpriteComponent->SetBoundMin(Vector3(0.0f, 0.0f, 1.0f));
		pNpc1SpriteComponent->SetBoundMax(Vector3(35.0f, 35.0f, 1.0f));
		pNpc1SpriteComponent->SetDefaultState(SpriteStates::STATIONARY);
		pNpc1SpriteComponent->SetDefaultDirection(SpriteDirections::LEFT);
		pNpc1SpriteComponent->SetZIndex(RenderableIndex::OBJECT_INDEX_HIGH);
	}
	owner->AddComponent<LittlePolygotMovementComponent>();
	LittlePolygotMovementComponent* pNpcMovementComponent = component_cast<LittlePolygotMovementComponent>(owner);
	if (pNpcMovementComponent)
	{
		pNpcMovementComponent->AttachRenderableTransform(pNpc1SpriteComponent);
		Vector3 position = Vector3(objMapData->GetX(), objMapData->GetY(), 0);
		pNpcMovementComponent->SetTranslation(&position);
		pNpcMovementComponent->SetMovementSupported(false);
		pNpcMovementComponent->SetGravitySupported(false);
	}
	owner->AddComponent<CollisionComponent>();
	CollisionComponent* pNpcCollisionComponent = component_cast<CollisionComponent>(owner);
	if (pNpcCollisionComponent)
	{
		pNpcCollisionComponent->AttachRenderable(&pNpc1SpriteComponent->GetRenderable());
		pNpcCollisionComponent->AddEventListener(pNpcMovementComponent);
		pNpcCollisionComponent->SetActive(true);
	}
	owner->AddComponent<BulletComponent>();
	BulletComponent* pNpcBulletComponent = component_cast<BulletComponent>(owner);

	if (pNpcBulletComponent)
	{
		pNpcBulletComponent->SetVelocity(GameResources::CONST_BULLET_VELOCITY_X, GameResources::CONST_BULLET_VELOCITY_Y);
		pNpcBulletComponent->SetDelay(GameResources::CONST_BULLET_DELAY_TIME);
		pNpcBulletComponent->SetSpawnOffset(0.0f, 0.0f);

		Vector3 velocity;

		float PI = 3.14159265f;
		float radian;
		int startDegree = 0;
		int velX, velY;

		int rockman_bullet_counts = 10;
		for (int i = 0; i < rockman_bullet_counts; i++)
		{
			
			radian = (float)(startDegree * PI) / 180.0f;
			velX = cos(radian) * 300.0f;
			velY = sin(radian) * 300.0f;
			startDegree += 20;
			
			velocity.m_x = velX;
			velocity.m_y = velY;
			velocity.m_z = -1.0f;
			
			GameObject* rockmanBullet = new GameObject(Utils::getNextId());
			rockmanBullet->SetResId(GameResources::NPC_BULLET);
			rockmanBullet->SetTag("NPC Bullet");
			rockmanBullet->AddComponent<SpriteComponent>();
			SpriteComponent* pRockmanBulletComponent = component_cast<SpriteComponent>(rockmanBullet);
			if (pRockmanBulletComponent)
			{
				Animation* bulletFiring = Animation::CreateAnimation(GameResources::MAP1_FIVESTARSHOOTER, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);

				pRockmanBulletComponent->RegisterState(BulletStates::FIRE, SpriteDirections::LEFT, bulletFiring);
				pRockmanBulletComponent->RegisterState(BulletStates::FIRE, SpriteDirections::RIGHT, bulletFiring);
				pRockmanBulletComponent->SetTag("Bullet");
				pRockmanBulletComponent->SetDebug(true);
				pRockmanBulletComponent->SetUseBounds(true);
				pRockmanBulletComponent->SetDebug(false);
				
				pRockmanBulletComponent->SetVelocity(velocity);
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
				//Vector3 position = Vector3(300 + i * 50, 200, 0);
				Vector3 position = Vector3(0, 0, 0);
				pRockmanBulletTransformComponent->SetTranslation(&position);
			}
			rockmanBullet->AddComponent<CollisionComponent>();
			CollisionComponent* pBulletCollisionComponent = component_cast<CollisionComponent>(rockmanBullet);
			if (pBulletCollisionComponent)
			{
				pBulletCollisionComponent->AttachRenderable(&pRockmanBulletComponent->GetRenderable());
				pBulletCollisionComponent->AddEventListener(pNpcBulletComponent);
				pBulletCollisionComponent->SetActive(true);
			}

			rockmanBullet->AddComponent<LifeTimeComponent>();
			LifeTimeComponent* pLifeTimeComponent = component_cast<LifeTimeComponent>(rockmanBullet);
			if (pLifeTimeComponent)
			{
				pLifeTimeComponent->SetLifeTime(GameResources::CONST_BULLET_LIFETIME);
			}

			pNpcBulletComponent->AddBullet(rockmanBullet);
		}//end for rockman_bullet_counts
	}//end if pBulletComponent
}

void MegamanMap1Factory::_createWallShooter(Framework::GameObject* owner, void* pData)
{
	owner->SetTag("Five Star Shooter");
	owner->SetResId(GameResources::WALL_SHOOTER);
	ObjectMapData* objMapData = static_cast<ObjectMapData*>(pData);
	assert(objMapData);
	AnimCache* npcPropLoader = new AnimCache("Resources\\Texture\\Map1\\npc_map1.plist");
	npcPropLoader->Load();
	owner->AddComponent<SpriteComponent>();
	SpriteComponent* pNpc1SpriteComponent = component_cast<SpriteComponent>(owner);
	if (pNpc1SpriteComponent)
	{
		Animation* stationayryAnim = Animation::CreateAnimation(GameResources::MAP1_NPC_WALL_SHOOTER, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);
		Animation* firingAnim = Animation::CreateAnimation(GameResources::MAP1_NPC_WALL_SHOOTER, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 1, 3);

		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::LEFT, stationayryAnim);
		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::RIGHT, stationayryAnim);
		pNpc1SpriteComponent->RegisterState(SpriteStates::FIRING, firingAnim);
		
		pNpc1SpriteComponent->SetTag("npc");
		pNpc1SpriteComponent->SetUseBounds(true);
		pNpc1SpriteComponent->SetRenderTransform(true);
		pNpc1SpriteComponent->SetBoundMin(Vector3(0.0f, 0.0f, 1.0f));
		pNpc1SpriteComponent->SetBoundMax(Vector3(35.0f, 35.0f, 1.0f));
		pNpc1SpriteComponent->SetDefaultState(SpriteStates::STATIONARY);
		pNpc1SpriteComponent->SetDefaultDirection(SpriteDirections::LEFT);
		pNpc1SpriteComponent->SetZIndex(RenderableIndex::OBJECT_INDEX_HIGH);
	}
	owner->AddComponent<LittlePolygotMovementComponent>();
	LittlePolygotMovementComponent* pNpcMovementComponent = component_cast<LittlePolygotMovementComponent>(owner);
	if (pNpcMovementComponent)
	{
		pNpcMovementComponent->AttachRenderableTransform(pNpc1SpriteComponent);
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

void MegamanMap1Factory::_createGreenRobocop(Framework::GameObject* owner, void* pData)
{
	owner->SetTag("Five Star Shooter");
	owner->SetResId(GameResources::GREEN_ROBOCOP);
	ObjectMapData* objMapData = static_cast<ObjectMapData*>(pData);
	assert(objMapData);
	AnimCache* npcPropLoader = new AnimCache("Resources\\Texture\\Map1\\npc_map1.plist");
	npcPropLoader->Load();
	owner->AddComponent<SpriteComponent>();
	SpriteComponent* pNpc1SpriteComponent = component_cast<SpriteComponent>(owner);
	if (pNpc1SpriteComponent)
	{
		Animation* stationayryAnim = Animation::CreateAnimation(GameResources::MAP1_NPC_GREEN_ROBOCOP, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 1, 1);
		Animation* firingAnim = Animation::CreateAnimation(GameResources::MAP1_NPC_GREEN_ROBOCOP, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 1, 3);

		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::LEFT, stationayryAnim);
		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::RIGHT, stationayryAnim);
		pNpc1SpriteComponent->RegisterState(SpriteStates::FIRING, firingAnim);

		pNpc1SpriteComponent->SetTag("npc");
		pNpc1SpriteComponent->SetUseBounds(true);
		pNpc1SpriteComponent->SetRenderTransform(true);
		pNpc1SpriteComponent->SetBoundMin(Vector3(0.0f, 0.0f, 1.0f));
		pNpc1SpriteComponent->SetBoundMax(Vector3(35.0f, 35.0f, 1.0f));
		pNpc1SpriteComponent->SetDefaultState(SpriteStates::STATIONARY);
		pNpc1SpriteComponent->SetDefaultDirection(SpriteDirections::LEFT);
		pNpc1SpriteComponent->SetZIndex(RenderableIndex::OBJECT_INDEX_HIGH);
	}
	owner->AddComponent<LittlePolygotMovementComponent>();
	LittlePolygotMovementComponent* pNpcMovementComponent = component_cast<LittlePolygotMovementComponent>(owner);
	if (pNpcMovementComponent)
	{
		pNpcMovementComponent->AttachRenderableTransform(pNpc1SpriteComponent);
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

void MegamanMap1Factory::_createBossBombMan(Framework::GameObject* owner, void* pData)
{
	owner->SetTag("Boss Bomb Man");
	owner->SetResId(GameResources::BOSS_BOMBMAN);
	ObjectMapData* objMapData = static_cast<ObjectMapData*>(pData);
	assert(objMapData);
	AnimCache* npcPropLoader = new AnimCache("Resources\\Texture\\Map1\\npc_map1.plist");
	npcPropLoader->Load();
	owner->AddComponent<SpriteComponent>();
	SpriteComponent* pNpc1SpriteComponent = component_cast<SpriteComponent>(owner);
	if (pNpc1SpriteComponent)
	{
		Animation* stationayryAnim = Animation::CreateAnimation(GameResources::MAP1_NPC_BOSS_BOMBMAN, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);
		Animation* firingAnim = Animation::CreateAnimation(GameResources::MAP1_NPC_BOSS_BOMBMAN, npcPropLoader, GameResources::CONST_SPRITE_ANIMATION_TIME, 1, 3);

		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::LEFT, stationayryAnim);
		pNpc1SpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::RIGHT, stationayryAnim);
		pNpc1SpriteComponent->RegisterState(SpriteStates::FIRING, firingAnim);

		pNpc1SpriteComponent->SetTag("npc");
		pNpc1SpriteComponent->SetUseBounds(true);
		pNpc1SpriteComponent->SetRenderTransform(true);
		pNpc1SpriteComponent->SetBoundMin(Vector3(10.0f, 0.0f, 1.0f));
		pNpc1SpriteComponent->SetBoundMax(Vector3(40.0f, 50.0f, 1.0f));
		pNpc1SpriteComponent->SetDefaultState(SpriteStates::STATIONARY);
		pNpc1SpriteComponent->SetDefaultDirection(SpriteDirections::LEFT);
		pNpc1SpriteComponent->SetZIndex(RenderableIndex::OBJECT_INDEX_HIGH);
	}
	owner->AddComponent<LittlePolygotMovementComponent>();
	LittlePolygotMovementComponent* pNpcMovementComponent = component_cast<LittlePolygotMovementComponent>(owner);
	if (pNpcMovementComponent)
	{
		pNpcMovementComponent->AttachRenderableTransform(pNpc1SpriteComponent);
		Vector3 position = Vector3(objMapData->GetX(), objMapData->GetY(), 0);
		pNpcMovementComponent->SetTranslation(&position);
		pNpcMovementComponent->SetHealth(5000);
	}
	owner->AddComponent<HealthBarComponent>();
	HealthBarComponent* pHealthBarComponent = component_cast<HealthBarComponent>(owner);
	if (pHealthBarComponent)
	{
		AnimCache* healBarProp = new AnimCache("Resources\\Texture\\Map1\\health-bar-npc.plist");
		healBarProp->Load();
		Animation* healthBarForeground = Animation::CreateAnimation(GameResources::MAP1_BOMMAN_HEALTH_BAR, healBarProp, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);
		Animation* healthBarBackground = Animation::CreateAnimation(GameResources::MAP1_BACKGROUND_HEALTH_BAR, healBarProp, GameResources::CONST_SPRITE_ANIMATION_TIME, 0, 1);


		pHealthBarComponent->GetBarSpriteComponent().RegisterState(SpriteStates::STATIONARY, healthBarBackground);
		pHealthBarComponent->GetHealthSpriteComponent().RegisterState(SpriteStates::STATIONARY, healthBarForeground);
		pHealthBarComponent->AttachHealthFunc(pNpcMovementComponent);
		Vector3 barPosition = Vector3(90, 450, 0);
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
	CollisionComponent* pNpcCollisionComponent = component_cast<CollisionComponent>(owner);
	if (pNpcCollisionComponent)
	{
		pNpcCollisionComponent->AttachRenderable(&pNpc1SpriteComponent->GetRenderable());
		pNpcCollisionComponent->AddEventListener(pNpcMovementComponent);
		pNpcCollisionComponent->SetActive(true);
	}
}