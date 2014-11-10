#include "Chapter6Task.h"
#include "Framework\Utilities\TmxLoader.h"

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

	m_playerObject.AddComponent<RenderableComponent>();
	RenderableComponent* pRenderComponent = component_cast<RenderableComponent>(m_playerObject);
	if(pRenderComponent)
	{
		Texture* texture = GetTexture("mariobig.png");
		RECT srect;
		srect.left = 0;
		srect.top = 0;
		srect.right = srect.left + texture->GetWidth() /5;
		srect.bottom = srect.top + texture->GetHeight() /2;
		TextureRegion *tregion = new TextureRegion(texture, srect);

		Renderable& renderable = pRenderComponent->GetRenderable();

		renderable.SetTextureRegion(tregion);

		Framework::AttachEvent(Framework::RENDER_EVENT, *pRenderComponent);
	}

	m_playerObject.AddComponent<TransformComponent>();
	TransformComponent* pTransformComponent = component_cast<TransformComponent>(m_playerObject);
	if(pTransformComponent)
	{
		Transform& transform = pTransformComponent->GetTransform();
		Vector3 position = Vector3(0, 100, 0);
		transform.SetTranslation(position);
	}

	m_playerObject.AddComponent<MovementComponent>();
	MovementComponent* pMovementComponent = component_cast<MovementComponent>(m_playerObject);
	if(pMovementComponent)
	{

	}

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
		
		
		
		/*D3DXVECTOR3 position(0, 0, 0);

		
		renderable.SetPosition(position);*/
	}

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