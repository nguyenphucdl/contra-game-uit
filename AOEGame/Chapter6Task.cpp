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
	
	
}

bool Chapter6Task::Start()
{
	// Test
	TmxLoader *tmxLoader = new TmxLoader("Contra-stage-1-mapfinal.tmx");
	tmxLoader->Load();
	
	TileMap* tileMap = tmxLoader->GetTileMap();
	tileMap->Init();


	Log::info(Log::LOG_LEVEL_MIN, "[Chapter6Task] Start... !\n");
	RegisterTexture("mariobig.png");	
	RegisterTexture("ContraSpriteFull.png");
	///TextureLoad();///////////////////////////////////////////////////////////////////



	// TILEMAP OBJECT
	m_tileMapObject.AddComponent<TileMapComponent>();
	TileMapComponent* pTileMapComponent = component_cast<TileMapComponent>(m_tileMapObject);
	if (pTileMapComponent)
	{
		pTileMapComponent->SetTileMap(tileMap);
		Renderable& renderable = pTileMapComponent->GetRenderable();
		Vector3 tileMapOrigin = Vector3(0, 480, 1);
		renderable.SetOrigin(tileMapOrigin);
		renderable.SetRenderTransform(false);

		pTileMapComponent->Initialize();
	}
	
	

	//PLAYER OBJECT
	m_playerObject.AddComponent<SpriteComponent>();
	SpriteComponent* pSpriteComponent = component_cast<SpriteComponent>(m_playerObject);
	if (pSpriteComponent)
	{
		Texture* sheet = GetTexture("ContraSpriteFull.png");
		Animation* moveLeftAnim = Animation::CreateAnimation("moveLeftAnim", 333.0f, sheet, 10, 10, 3, 20);
		Animation* moveRightAnim = Animation::CreateAnimation("moveRightAnim", 333.0f, sheet, 10, 10, 3, 23);
		Animation* jumpRightAnim = Animation::CreateAnimation("jumpRightAnim", 333.0f, sheet, 10, 10, 4, 50);
		Animation* jumpLeftAnim = Animation::CreateAnimation("jumpLeftAnim", 333.0f, sheet, 10, 10, 4, 54);
		Animation* sitLeftAnim = Animation::CreateAnimation("sitLeft", 333.0f, sheet, 10, 10, 1, 8);
		Animation* sitRightAnim = Animation::CreateAnimation("sitRight", 33.0f, sheet, 10, 10, 1, 9);

		Vector3 position = Vector3(100, 100, 0);
		pSpriteComponent->SetRenderTransform(false);
		pSpriteComponent->SetOrigin(position);

		pSpriteComponent->RegisterState(SpriteState::MOVELEFT, moveLeftAnim);
		pSpriteComponent->RegisterState(SpriteState::MOVERIGHT, moveRightAnim);
		pSpriteComponent->RegisterState(SpriteState::JUMPUPLEFT, jumpLeftAnim);
		pSpriteComponent->RegisterState(SpriteState::JUMPUPRIGHT, jumpRightAnim);
		pSpriteComponent->RegisterState(SpriteState::SITLEFT, sitLeftAnim);
		pSpriteComponent->RegisterState(SpriteState::SITRIGHT, sitRightAnim);
		pSpriteComponent->SetDefaultState(SpriteState::MOVELEFT);
		pSpriteComponent->Initialize();
	}
	m_playerObject.AddComponent<TransformComponent>();
	TransformComponent* pPlayerTransformComponent = component_cast<TransformComponent>(m_playerObject);
	if (pPlayerTransformComponent)
	{
		pPlayerTransformComponent->SetTransform(&pSpriteComponent->GetRenderable().GetTransform());
		Transform* transform = pPlayerTransformComponent->GetTransform();
		Vector3 translation = Vector3(0, 0, 0);
		transform->SetTranslation(translation);
	}
	m_playerObject.AddComponent<MovementComponent>();
	MovementComponent* pPlayerMovementComponent = component_cast<MovementComponent>(m_playerObject);
	if (pPlayerMovementComponent)
	{
		Vector3 velocity = Vector3(50.0f, 50.0f, 0);
		pPlayerMovementComponent->SetVelocity(velocity);
		pPlayerMovementComponent->Initialize();
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
	Framework::SendEvent(Events::UPDATE_EVENT); // need refactor
	Framework::SendEvent(Events::POST_UPDATE_EVENT);
	Framework::SendEvent(Events::RENDER_EVENT);
}

void Chapter6Task::OnResume()
{
}

void Chapter6Task::Stop()
{
}