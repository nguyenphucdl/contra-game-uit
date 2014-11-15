#include "Chapter6Task.h"
#include "Framework\Utilities\TmxLoader.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"

Chapter6Task::Chapter6Task(const unsigned int priority)
	: Task(priority, "Chapter6Task")
{
}

Chapter6Task::~Chapter6Task()
{
}

void Chapter6Task::HandleEvent(Event* pEvent)
{
	assert(pEvent);

	if(pEvent->GetID() == Framework::KEYDOWN_EVENT)
	{
		int i = (int)pEvent->GetData();
		Log::info(Log::LOG_LEVEL_ROOT, "[Chapter6Task] Receive KEYCODE %d !\n", i);
		if(i > 0)
		{
			Framework::SendEvent(JUMP_EVENT, NULL);
		}
	}
	
}

bool Chapter6Task::Start()
{
	Framework::AttachEvent(Framework::KEYDOWN_EVENT, *this);
	Framework::AttachEvent(Framework::KEYUP_EVENT, *this);

	// Test
	TmxLoader *tmxLoader = new TmxLoader("map1-2.tmx");
	tmxLoader->Load();
	
	TileMap* tileMap = tmxLoader->GetTileMap();
	tileMap->Init();


	Log::info(Log::LOG_LEVEL_MIN, "[Chapter6Task] Start... !\n");
	RegisterTexture("mariobig.png");
	///TextureLoad();///////////////////////////////////////////////////////////////////

	RegisterEvent(UPDATE_EVENT);
	RegisterEvent(POSTUPDATE_EVENT);
	RegisterEvent(RENDER_EVENT);
	RegisterEvent(JUMP_EVENT);


	// TILEMAP OBJECT
	m_tileMapObject.AddComponent<TileMapComponent>();
	TileMapComponent* pTileMapComponent = component_cast<TileMapComponent>(m_tileMapObject);
	if (pTileMapComponent)
	{
		pTileMapComponent->SetTileMap(tileMap);
		
		pTileMapComponent->Initialize();
		Framework::AttachEvent(Framework::RENDER_EVENT, *pTileMapComponent);
	}
	m_tileMapObject.AddComponent<TransformComponent>();
	TransformComponent* pTileMapTransformComponent = component_cast<TransformComponent>(m_tileMapObject);
	if (pTileMapTransformComponent)
	{
		pTileMapTransformComponent->SetTransform(&pTileMapComponent->GetRenderable().GetTransform());
		Transform* transform = pTileMapTransformComponent->GetTransform();
		
		Vector3 position = Vector3(0, 0, 0);
		transform->SetTranslation(position);
	}
	
	// PLAYER OBJECT
	m_playerObject.AddComponent<SpriteComponent>();
	SpriteComponent* pSpriteComponent = component_cast<SpriteComponent>(m_playerObject);
	if (pSpriteComponent)
	{
		Texture* sheet = GetTexture("mariobig.png");
		Animation* moveRightAnim = Animation::CreateAnimation("moveRightAnim", 0.15f, sheet, 5, 2, 4, 0, true);
		Animation* moveLeftAnim = Animation::CreateAnimation("moveLeftAnim", 0.15f, sheet, 5, 2, 4, 6);
		Animation* sitLeftAnim = Animation::CreateAnimation("sitLeftAnim", 0.15f, sheet, 5, 2, 1, 5);
		Animation* sitRightAnim = Animation::CreateAnimation("sitRightAnim", 0.15f, sheet, 5, 2, 1, 4);

		pSpriteComponent->RegisterState(SpriteState::MOVELEFT, moveLeftAnim);
		pSpriteComponent->RegisterState(SpriteState::MOVERIGHT, moveRightAnim);
		pSpriteComponent->RegisterState(SpriteState::SITLEFT, sitLeftAnim);
		pSpriteComponent->RegisterState(SpriteState::SITRIGHT, sitRightAnim);
		pSpriteComponent->SetDefaultState(SpriteState::MOVERIGHT);
		pSpriteComponent->Initialize();
	}
	m_playerObject.AddComponent<TransformComponent>();
	TransformComponent* pTransformComponent = component_cast<TransformComponent>(m_playerObject);
	if (pTransformComponent)
	{
		pTransformComponent->SetTransform(&pSpriteComponent->GetRenderable().GetTransform());
		Transform* transform = pTransformComponent->GetTransform();
		Vector3 position = Vector3(100, 50, 0);
		transform->SetTranslation(position);
	}
	m_playerObject.AddComponent<MovementComponent>();
	MovementComponent* pMovementComponent = component_cast<MovementComponent>(m_playerObject);
	if (pMovementComponent)
	{
		pMovementComponent->SetVelocityX(100.0f);
		pMovementComponent->Initialize();
	}

	// CAMERA OBJECT
	m_cameraObject.AddComponent<CameraComponent>();
	CameraComponent *pCameraComponent = component_cast<CameraComponent>(m_cameraObject);
	if (pCameraComponent)
	{
		pCameraComponent->AttachObject(&m_playerObject);
		pCameraComponent->Initialize();
	}

	return true;
}

void Chapter6Task::OnSuspend()
{
}

void Chapter6Task::Update()
{
	Framework::SendEvent(Framework::UPDATE_EVENT);
	Framework::SendEvent(Framework::POSTUPDATE_EVENT);
	Framework::SendEvent(Framework::RENDER_EVENT);
}

void Chapter6Task::OnResume()
{
}

void Chapter6Task::Stop()
{
}