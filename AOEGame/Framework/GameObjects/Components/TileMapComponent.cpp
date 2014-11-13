#include "TileMapComponent.h"
#include "../GameObject.h"
#include "../../Renderer/Texture/TextureManager.h"
#include "TransformComponent.h"
namespace Framework
{
	TileMapComponent::TileMapComponent(GameObject* pOwner)
		:	Component(pOwner)
	{
		m_tileMap = NULL;
		m_initilize = false;
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
		
		assert(Renderer::GetSingletonPtr());
		Renderer::GetSingleton().AddRenderable(&m_renderable);
	}

	void TileMapComponent::HandleEvent(Event* pEvent)
	{
	}
}