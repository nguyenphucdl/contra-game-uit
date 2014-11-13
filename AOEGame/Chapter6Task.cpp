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
	m_tileMapObject.AddComponent<TransformComponent>();
	TransformComponent* pTileMapTransformComponent = component_cast<TransformComponent>(m_tileMapObject);
	if (pTileMapTransformComponent)
	{
		Transform& transform = pTileMapTransformComponent->GetTransform();
		//Vector3 position = Vector3(0, 100, 0);
		//transform.SetTranslation(position);
		transform.SetScale(2.6f);
	}
	m_tileMapObject.AddComponent<TileMapComponent>();
	TileMapComponent* pTileMapComponent = component_cast<TileMapComponent>(m_tileMapObject);
	if (pTileMapComponent)
	{
		pTileMapComponent->SetTileMap(tileMap);
		Texture* tilemapTexture = GetTexture(tileMap->GetTag());
		// Get viewport
		RECT vport;
		vport.left = 0;
		vport.right = 800;
		vport.top = 0;
		vport.bottom = 600;
		TextureRegion *tileMapRegion = new TextureRegion(tilemapTexture, vport);

		Renderable& tilemapRenderable = pTileMapComponent->GetRenderable();

		tilemapRenderable.SetTextureRegion(tileMapRegion);
		pTileMapComponent->Initialize();
		Framework::AttachEvent(Framework::RENDER_EVENT, *pTileMapComponent);
	}

	//Test
	//Texture* sheet = GetTexture("mariobig.png");
	//m_animation = Animation::CreateAnimation("anim1", 0.15f, sheet, 5, 2, 5);

	/*m_playerObject.AddComponent<RenderableComponent>();
	RenderableComponent* pRenderComponent = component_cast<RenderableComponent>(m_playerObject);
	if(pRenderComponent)
	{
		TextureRegion* tregion = m_animation->Next();

		Renderable& renderable = pRenderComponent->GetRenderable();

		renderable.SetTextureRegion(tregion);
		pRenderComponent->Initialize();
		Framework::AttachEvent(Framework::RENDER_EVENT, *pRenderComponent);
	}*/
	m_playerObject.AddComponent<TransformComponent>();
	TransformComponent* pTransformComponent = component_cast<TransformComponent>(m_playerObject);
	if (pTransformComponent)
	{
		Transform& transform = pTransformComponent->GetTransform();
		Vector3 position = Vector3(0, 0, 0);
		transform.SetTranslation(position);
	}
	m_playerObject.AddComponent<SpriteComponent>();
	SpriteComponent* pSpriteComponent = component_cast<SpriteComponent>(m_playerObject);
	if (pSpriteComponent)
	{
		Texture* sheet = GetTexture("mariobig.png");
		Animation* moveRightAnim = Animation::CreateAnimation("moveRightAnim", 0.15f, sheet, 5, 2, 4);
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
	m_playerObject.AddComponent<MovementComponent>();
	MovementComponent* pMovementComponent = component_cast<MovementComponent>(m_playerObject);
	if (pMovementComponent)
	{
		pMovementComponent->SetVelocityX(100.0f);
		pMovementComponent->Initialize();
	}

	

	/*m_playerObject.AddComponent<MovementComponent>();
	MovementComponent* pMovementComponent = component_cast<MovementComponent>(m_playerObject);
	if(pMovementComponent)
	{

	}*/

	m_playerObject.AddComponent<CameraComponent>();
	CameraComponent *pCameraComponent = component_cast<CameraComponent>(m_playerObject);
	if(pCameraComponent)
	{
		Framework::AttachEvent(Framework::POSTUPDATE_EVENT, *pCameraComponent);
	}


	return true;
}

void Chapter6Task::OnSuspend()
{
}

void Chapter6Task::Update()
{
	RenderableComponent* pRenderComponent = component_cast<RenderableComponent>(m_playerObject);
	if (pRenderComponent)
	{
		TextureRegion* tregion = m_animation->Next();

		Renderable& renderable = pRenderComponent->GetRenderable();

		renderable.SetTextureRegion(tregion);
	}

	/*RenderableComponent* pRenderComponent = component_cast<RenderableComponent>(m_playerObject);
	if(pRenderComponent)
	{
		Renderable& renderable = pRenderComponent->GetRenderable();
		Texture* texture = GetTexture("mariobig.png");
		if(Timer::GetSingletonPtr()->GetTimeTotal() > MIN_FRAME_RATE / 100.0f)
		{
			RECT srect = renderable.GetTextureRegion()->GetRect();
			srect.left += texture->GetWidth() /5;
			
			

			if(srect.left > texture->GetWidth())
				srect.left = 0;

			srect.right = srect.left + texture->GetWidth() / 5;
			TextureRegion *tregion = new TextureRegion(texture, srect);
			renderable.SetTextureRegion(tregion);
			Timer::GetSingletonPtr()->Reset();
		}
	}*/

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