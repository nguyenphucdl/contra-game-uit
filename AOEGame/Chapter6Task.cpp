#include "Chapter6Task.h"
#include "Framework\Utilities\TmxLoader.h"
#include "Framework\GameObjects\Components\SpriteComponent.h"
#include "Framework\Utilities\Console.h"
#include "Framework\Utilities\AnimCache.h"

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
	/*Font *font = new Font();
	font->setCharSize(14, 16);
	font->setColumns(16);
	font->Print(100, 100, "HELLO WORLD!");*/

	Console* console = new Console();
	console->init();
	//console->print("Hello World!");
	//console->print("Nguyen Hong Phuc!", 3);
	
	
	//Test
	//std::ostringstream os;
	//os.str("");
	//os << "TIMER " << (float)Timer::GetSingletonPtr()->GetTimeSim() << "!";
	//console->print(os.str());

	//Property* propLoader = new Property("Resources\\TestTexturePacker.plist");
	//propLoader->Load();

	// Test
	TmxLoader *tmxLoader = new TmxLoader("Resources\\Maps\\Scence1-Map1\\Scence1-Map1.tmx");
	//TmxLoader *tmxLoader = new TmxLoader("Contra-stage-1-mapfinal.tmx");
	tmxLoader->Load();
	
	TileMap* tileMap = tmxLoader->GetTileMap();
	tileMap->Init();


	Log::info(Log::LOG_LEVEL_MIN, "[Chapter6Task] Start... !\n");

	RegisterTexture("ContraSpriteFull.png");




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
		pTileMapComponent->SetRenderTransform(false);
		pTileMapComponent->Initialize();
	}
	
	

	//PLAYER OBJECT
	m_playerObject.AddComponent<SpriteComponent>();
	SpriteComponent* pSpriteComponent = component_cast<SpriteComponent>(m_playerObject);
	if (pSpriteComponent)
	{
		Texture* sheet = GetTexture("ContraSpriteFull.png");
		//Animation* moveLeftAnim = Animation::CreateAnimation("moveLeftAnim", 333.0f, sheet, 10, 10, 3, 20);
		//moveLeftAnim->Reverse();
		//Animation* moveRightAnim = Animation::CreateAnimation("moveRightAnim", 333.0f, sheet, 10, 10, 3, 23);
		//Animation* jumpRightAnim = Animation::CreateAnimation("jumpRightAnim", 333.0f, sheet, 10, 10, 4, 50);
		//Animation* jumpLeftAnim = Animation::CreateAnimation("jumpLeftAnim", 333.0f, sheet, 10, 10, 4, 54);
		//Animation* sitLeftAnim = Animation::CreateAnimation("sitLeft", 333.0f, sheet, 10, 10, 1, 8);
		//Animation* sitRightAnim = Animation::CreateAnimation("sitRight", 33.0f, sheet, 10, 10, 1, 9);
		//Animation* stationaryRight = Animation::CreateAnimation("stationayRight", 33.0f, sheet, 10, 10, 1, 23);
		//Animation* stationaryLeft = Animation::CreateAnimation("stationaryLeft", 33.0f, sheet, 10, 10, 1, 22);

		Vector3 position = Vector3(0, 100, 0);
		pSpriteComponent->SetRenderTransform(false);
		//pSpriteComponent->SetOrigin(position);

		/*pSpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::LEFT, stationaryLeft);
		pSpriteComponent->RegisterState(SpriteStates::STATIONARY, SpriteDirections::RIGHT, stationaryRight);
		pSpriteComponent->RegisterState(SpriteStates::MOVE, SpriteDirections::LEFT, moveLeftAnim);
		pSpriteComponent->RegisterState(SpriteStates::MOVE, SpriteDirections::RIGHT, moveRightAnim);
		pSpriteComponent->RegisterState(SpriteStates::JUMP, SpriteDirections::RIGHT, jumpRightAnim);
		pSpriteComponent->RegisterState(SpriteStates::JUMP, SpriteDirections::LEFT, jumpLeftAnim);
		pSpriteComponent->RegisterState(SpriteStates::SIT, SpriteDirections::RIGHT, sitRightAnim);
		pSpriteComponent->RegisterState(SpriteStates::SIT, SpriteDirections::LEFT, sitLeftAnim);*/

		pSpriteComponent->SetDefaultState(SpriteStates::STATIONARY);
		pSpriteComponent->SetDefaultDirection(SpriteDirections::RIGHT);
		pSpriteComponent->Initialize();
	}
	

	m_playerObject.AddComponent<PlayerMovementComponent>();
	PlayerMovementComponent* pPlayerTransformComponent = component_cast<PlayerMovementComponent>(m_playerObject);
	if (pPlayerTransformComponent)
	{
		pPlayerTransformComponent->AttachRenderableTransform(pSpriteComponent);
		Vector3 translation = Vector3(100, 0, 0);
		pPlayerTransformComponent->SetTranslation(&translation);
		pPlayerTransformComponent->Initialize();
	}

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
		pCameraComponent->SetViewportOrigin(0, 0);
		//pCameraComponent->SetViewportTranslate(0, 0);
		pCameraComponent->Initialize();
	}

	
	Log::printComponentIDs();
	Log::printMapEvents();

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