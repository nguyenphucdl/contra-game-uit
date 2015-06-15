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
#include "PlayerMovementComponent.h"
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
	if (objType == GameResources::GameObjectIds::LITTLE_POGOBOT)
	{
		_createLittlePogobot(owner, pData);
	}
}

void MegamanMap1Factory::_createLittlePogobot(Framework::GameObject* owner, void* pData)
{
	ObjectMapData* objMapData = static_cast<ObjectMapData*>(pData);
	assert(objMapData);
	AnimCache* npcPropLoader = new AnimCache("Resources\\Texture\\Map1\\npc.plist");
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
		pNpc1SpriteComponent->SetBoundMax(Vector3(30.0f, 30.0f, 1.0f));
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
	}
}