#include "TileMapComponent.h"
#include "../GameObject.h"
#include "../../EventManager/EventManager.h"
#include "../../Renderer/Texture/TextureManager.h"
#include "../../Utilities/Timer.h"
#include "TransformComponent.h"
namespace Framework
{
	TileMapComponent::TileMapComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_scroll(false)
		, m_tileMap(NULL)
		, m_mapViewport(NULL)
	{
		Framework::AttachEvent(KEYDOWN_EVENT, *this);
		Framework::AttachEvent(KEYUP_EVENT, *this);
		Framework::AttachEvent(UPDATE_EVENT, *this);
		Framework::AttachEvent(RENDER_EVENT, *this);
	}

	TileMapComponent::~TileMapComponent()
	{
	}

	void TileMapComponent::Initialize()
	{
		Log::info(Log::LOG_LEVEL_ROOT, "[TileMapComponent] Initialize...\n");
		if(m_tileMap == NULL)
		{
			Log::error("TileMap not set in component !");
			throw new GameError(GameErrorNS::FATAL_ERROR, "TileMap not set in component !");
		}
		RECT vport = Renderer::GetSingletonPtr()->GetViewport();
		Texture* tilemapTexture = GetTexture(m_tileMap->GetTag());
		TextureRegion *tileMapRegion = new TextureRegion(tilemapTexture, vport);
		m_mapViewport = &tileMapRegion->GetRect();
		m_renderable.SetTextureRegion(tileMapRegion);

		

		assert(Renderer::GetSingletonPtr());
		Renderer::GetSingleton().AddRenderable(&m_renderable);
	}

	void TileMapComponent::UpdateMapView(RECT& view)
	{
		m_mapViewport->left = view.left;
		m_mapViewport->right = view.right;
		m_mapViewport->top = view.top;
		m_mapViewport->bottom = view.bottom;
	}

	void TileMapComponent::HandleEvent(Event* pEvent)
	{
		switch (pEvent->GetID())
		{
		case KEYDOWN_EVENT:
			m_scroll = true;
			break;
		case KEYUP_EVENT:
			m_scroll = false;
			break;
		case UPDATE_EVENT:
			

			break;
		case RENDER_EVENT:
			UpdateMapView(Renderer::GetSingletonPtr()->GetViewport());
			break;
		default:
			m_scroll = false;
			break;
		}


	}
}