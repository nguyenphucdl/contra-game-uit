#include "TileMapComponent.h"
#include "../GameObject.h"
#include "../../EventManager/EventManager.h"
#include "../../Renderer/Texture/TextureManager.h"
#include "../../Utilities/Timer.h"
#include "../../Utilities/Console.h"
#include "TransformComponent.h"
namespace Framework
{
	TileMapComponent::TileMapComponent(GameObject* pOwner)
		: RenderableComponent(pOwner)
		, m_scroll(false)
		, m_tileMap(NULL)
		, m_mapViewport(NULL)
		, m_mapOrigin(0.0f, 0.0f, 0.0f)
	{
			
	}

	TileMapComponent::~TileMapComponent()
	{
	}

	void TileMapComponent::Initialize()
	{
		RenderableComponent::Initialize();

		Framework::AttachEvent(Events::SCE_PRE_RENDER_EVENT, *this);

		Log::info(Log::LOG_LEVEL_ROOT, "[TileMapComponent] Initialize...\n");
		if(m_tileMap == NULL)
		{
			Log::error("TileMap not set in component !");
			throw new GameError(GameErrorNS::FATAL_ERROR, "TileMap not set in component !");
		}
		Camera* sysCamera = &Renderer::GetSingletonPtr()->GetCamera();

		int viewWidth = sysCamera->GetViewPortWidth();
		int viewHeight = sysCamera->GetViewPortHeight();
		RECT mapBound = m_tileMap->GetBound();

		RECT vport;
		vport.left = mapBound.left;
		vport.right = viewWidth;
		vport.bottom = mapBound.bottom;
		vport.top = vport.bottom - viewHeight;
		//vport.top += 175;
		//vport.bottom += 175;
		Texture* tilemapTexture = GetTexture(m_tileMap->GetTag());
		TextureRegion *tileMapRegion = new TextureRegion(tilemapTexture, vport);
		m_mapViewport = &tileMapRegion->GetRect();
		m_renderable.SetTextureRegion(tileMapRegion);

		m_renderable.SetRenderTransform(false);//CHECK LATER!
		m_renderable.SetDebug(true);
	}

	void TileMapComponent::UpdateHorizontalScrollView(int x)
	{
		int delta = x - m_mapViewport->left;
		m_mapViewport->left += delta;
		m_mapViewport->right += delta;
	}

	void TileMapComponent::UpdateMapScrollView(Vector3& tranlate)
	{
		
		m_mapViewport->left = m_mapOrigin.m_x + tranlate.m_x;
		m_mapViewport->right = m_mapViewport->left + Renderer::GetSingletonPtr()->GetCamera().GetViewPortWidth();
		m_mapViewport->top = m_mapOrigin.m_y - tranlate.m_y;
		m_mapViewport->bottom = m_mapViewport->top + Renderer::GetSingletonPtr()->GetCamera().GetViewPortHeight();
	}

	void TileMapComponent::UpdateVerticalScrollView(int y)
	{
		int delta = y - m_mapViewport->top;
		m_mapViewport->top += delta;
		m_mapViewport->bottom += delta;
		//Console::GetSingletonPtr()->print("ScrollView top %d left %d", m_mapViewport->top, m_mapViewport->left);
	}


	void TileMapComponent::HandleEvent(Event* pEvent)
	{
		RenderableComponent::HandleEvent(pEvent);

		switch (pEvent->GetID())
		{
		case Events::SCE_PRE_RENDER_EVENT:
		{
			Renderer::GetSingletonPtr()->AddRenderable(&m_renderable);

			UpdateMapScrollView(Renderer::GetSingletonPtr()->GetCamera().GetViewTranslate());
			
			//UpdateHorizontalScrollView(Renderer::GetSingletonPtr()->GetCamera().GetViewPort().left);
			//UpdateVerticalScrollView(Renderer::GetSingletonPtr()->GetCamera().GetViewPort().top);
		}
			break;
		default:
			break;
		}
	}
}