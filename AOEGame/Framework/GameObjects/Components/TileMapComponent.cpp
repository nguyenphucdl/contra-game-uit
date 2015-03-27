#include "TileMapComponent.h"
#include "../GameObject.h"
#include "../../EventManager/EventManager.h"
#include "../../Renderer/Texture/TextureManager.h"
#include "../../Utilities/Timer.h"
#include "TransformComponent.h"
namespace Framework
{
	TileMapComponent::TileMapComponent(GameObject* pOwner)
		: RenderableComponent(pOwner)
		, m_scroll(false)
		, m_tileMap(NULL)
		, m_mapViewport(NULL)
	{
		Framework::AttachEvent(Events::PRE_RENDER_EVENT, *this);		
	}

	TileMapComponent::~TileMapComponent()
	{
	}

	void TileMapComponent::Initialize()
	{
		RenderableComponent::Initialize();

		Log::info(Log::LOG_LEVEL_ROOT, "[TileMapComponent] Initialize...\n");
		if(m_tileMap == NULL)
		{
			Log::error("TileMap not set in component !");
			throw new GameError(GameErrorNS::FATAL_ERROR, "TileMap not set in component !");
		}
		RECT vport = Renderer::GetSingletonPtr()->GetCamera().GetViewPort();
		Texture* tilemapTexture = GetTexture(m_tileMap->GetTag());
		TextureRegion *tileMapRegion = new TextureRegion(tilemapTexture, vport);
		m_mapViewport = &tileMapRegion->GetRect();
		m_renderable.SetTextureRegion(tileMapRegion);

		m_renderable.SetRenderTransform(false);
		//m_renderable.SetT
	}

	void TileMapComponent::UpdateMapView(RECT view)
	{
		m_mapViewport->left = view.left;
		m_mapViewport->right = view.right;
		m_mapViewport->top = view.top;
		m_mapViewport->bottom = view.bottom;
	}

	void TileMapComponent::UpdateHorizontalScrollView(int x)
	{
		int delta = x - m_mapViewport->left;
		m_mapViewport->left += delta;
		m_mapViewport->right += delta;
	}

	void TileMapComponent::UpdateVerticalScrollView(int y)
	{
		int delta = y - m_mapViewport->top;
		m_mapViewport->top += delta;
		m_mapViewport->bottom += delta;
	}

	void TileMapComponent::HandleEvent(Event* pEvent)
	{
		switch (pEvent->GetID())
		{
		case Events::KEY_DOWN_EVENT:
			m_scroll = true;
			break;
		case Events::KEY_UP_EVENT:
			m_scroll = false;
			break;
		
		case Events::PRE_RENDER_EVENT:
			UpdateHorizontalScrollView(Renderer::GetSingletonPtr()->GetCamera().GetViewPort().left);
			UpdateVerticalScrollView(Renderer::GetSingletonPtr()->GetCamera().GetViewPort().top);
			break;
		default:
			m_scroll = false;
			break;
		}


	}
}