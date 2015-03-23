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
	/*assert(pEvent);

	if(pEvent->GetID() == Framework::KEYDOWN_EVENT)
	{
		int i = (int)pEvent->GetData();
		Log::info(Log::LOG_LEVEL_ROOT, "[Chapter6Task] Receive KEYCODE %d !\n", i);
		if(i > 0)
		{
			Framework::SendEvent(JUMP_EVENT, NULL);
		}
	}*/
	
}

bool Chapter6Task::Start()
{
	//Framework::AttachEvent(Framework::KEYDOWN_EVENT, *this);
	//Framework::AttachEvent(Framework::KEYUP_EVENT, *this);

	// Test
	TmxLoader *tmxLoader = new TmxLoader("Contra-stage-1-mapfinal.tmx");
	tmxLoader->Load();
	
	TileMap* tileMap = tmxLoader->GetTileMap();
	tileMap->Init();


	Log::info(Log::LOG_LEVEL_MIN, "[Chapter6Task] Start... !\n");
	RegisterTexture("mariobig.png");	
	RegisterTexture("ContraSpriteFull.png");
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
		Renderable& renderable = pTileMapComponent->GetRenderable();
		Vector3 tileMapOrigin = Vector3(0, 480, 1);
		renderable.SetOrigin(tileMapOrigin);
		renderable.SetRenderTransform(false);

		pTileMapComponent->Initialize();
	}
	/*m_tileMapObject.AddComponent<TransformComponent>();
	TransformComponent* pTileMapTransformComponent = component_cast<TransformComponent>(m_tileMapObject);
	if (pTileMapTransformComponent)
	{
		pTileMapTransformComponent->SetTransform(&pTileMapComponent->GetRenderable().GetTransform());
		Transform* transform = pTileMapTransformComponent->GetTransform();
		
		Vector3 translation = Vector3(0, 100, 0);
		transform->SetTranslation(translation);
	}*/
	
	//// CONTRA FINAL OBJECT
	//m_contraFinalObject.AddComponent<SpriteComponent>();
	//SpriteComponent* pSpriteFinalComponent = component_cast<SpriteComponent>(m_contraFinalObject);
	//if (pSpriteFinalComponent)
	//{
	//	Texture* sheet = GetTexture("ContraSpriteFull.png");
	//	Animation* moveLeftAnim = Animation::CreateAnimation("moveLeftAnim", 0.15f, sheet, 10, 10, 3,  20);
	//	Animation* moveRightAnim = Animation::CreateAnimation("moveRightAnim", 0.15f, sheet, 10, 10, 3, 23);
	//	Animation* jumpRightAnim = Animation::CreateAnimation("jumpRightAnim", 0.15f, sheet, 10, 10, 4, 50);
	//	Animation* jumpLeftAnim = Animation::CreateAnimation("jumpLeftAnim", 0.15f, sheet, 10, 10, 4, 54);
	//	Animation* sitLeftAnim = Animation::CreateAnimation("sitLeft", 0.15f, sheet, 10, 10, 1, 8);
	//	Animation* sitRightAnim = Animation::CreateAnimation("sitRight", 0.15f, sheet, 10, 10, 1, 9);

	//	Vector3 position = Vector3(200, 100, 0);
	//	pSpriteFinalComponent->SetRenderTransform(false);
	//	pSpriteFinalComponent->SetOrigin(position);

	//	pSpriteFinalComponent->RegisterState(SpriteState::MOVELEFT, moveLeftAnim);
	//	pSpriteFinalComponent->RegisterState(SpriteState::MOVERIGHT, moveRightAnim);
	//	pSpriteFinalComponent->RegisterState(SpriteState::JUMPUPLEFT, jumpLeftAnim);
	//	pSpriteFinalComponent->RegisterState(SpriteState::JUMPUPRIGHT, jumpRightAnim);
	//	pSpriteFinalComponent->RegisterState(SpriteState::SITLEFT, sitLeftAnim);
	//	pSpriteFinalComponent->RegisterState(SpriteState::SITRIGHT, sitRightAnim);
	//	pSpriteFinalComponent->SetDefaultState(SpriteState::MOVELEFT);
	//	pSpriteFinalComponent->Initialize();
	//}
	//m_contraFinalObject.AddComponent<TransformComponent>();
	//TransformComponent* pTransformComponent = component_cast<TransformComponent>(m_contraFinalObject);
	//if (pTransformComponent)
	//{
	//	pTransformComponent->SetTransform(&pSpriteFinalComponent->GetRenderable().GetTransform());
	//	Transform* transform = pTransformComponent->GetTransform();
	//	Vector3 translation = Vector3(100, 150, 0);
	//	transform->SetTranslation(translation);
	//}
	//m_contraFinalObject.AddComponent<MovementComponent>();
	//MovementComponent* pMovementComponent = component_cast<MovementComponent>(m_contraFinalObject);
	//if (pMovementComponent)
	//{
	//	pMovementComponent->SetVelocityX(200.0f);
	//	pMovementComponent->Initialize();
	//}


	//PLAYER OBJECT
	m_playerObject.AddComponent<SpriteComponent>();
	SpriteComponent* pSpriteComponent = component_cast<SpriteComponent>(m_playerObject);
	if (pSpriteComponent)
	{
		Texture* sheet = GetTexture("ContraSpriteFull.png");
		Animation* moveLeftAnim = Animation::CreateAnimation("moveLeftAnim", 0.15f, sheet, 10, 10, 3, 20);
		Animation* moveRightAnim = Animation::CreateAnimation("moveRightAnim", 0.15f, sheet, 10, 10, 3, 23);
		Animation* jumpRightAnim = Animation::CreateAnimation("jumpRightAnim", 0.15f, sheet, 10, 10, 4, 50);
		Animation* jumpLeftAnim = Animation::CreateAnimation("jumpLeftAnim", 0.15f, sheet, 10, 10, 4, 54);
		Animation* sitLeftAnim = Animation::CreateAnimation("sitLeft", 0.15f, sheet, 10, 10, 1, 8);
		Animation* sitRightAnim = Animation::CreateAnimation("sitRight", 0.15f, sheet, 10, 10, 1, 9);

		Vector3 position = Vector3(100, 350, 0);
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
		Vector3 translation = Vector3(100, 150, 0);
		transform->SetTranslation(translation);
	}
	m_playerObject.AddComponent<MovementComponent>();
	MovementComponent* pPlayerMovementComponent = component_cast<MovementComponent>(m_playerObject);
	if (pPlayerMovementComponent)
	{
		pPlayerMovementComponent->SetVelocityX(100.0f);
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