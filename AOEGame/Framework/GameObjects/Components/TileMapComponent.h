#ifndef __TILEMAPCOMPONENT_H__
#define	__TILEMAPCOMPONENT_H__
#include "../../Application/Context.h"
#include "../Component.h"
#include "../../Renderer/Renderer.h"
#include "../../Renderer/Renderable.h"
#include "../../EventManager/Event.h"
#include "../../EventManager/EventHandler.h"
#include "../../EventManager/EventId.h"
#include "../../Renderer/Texture/Texture.h"
#include "../../Renderer/Texture/TextureRegion.h"
#include "../../TileMap/TileMap.h"
#include "RenderableComponent.h"

namespace Framework
{
	class TileMapComponent
		: public RenderableComponent
	{
	private:
		static const unsigned int s_id = ComponentIDs::TileMapComponentId;

		TileMap*				m_tileMap;		
		RECT*					m_mapViewport;
		bool					m_scroll;

	public:
		static unsigned int GetId() { return s_id; }

		explicit TileMapComponent(GameObject* pOwner);
		virtual ~TileMapComponent();

		virtual void Initialize();

		Renderable&	GetRenderable() { return RenderableComponent::m_renderable; }

		virtual void HandleEvent(Event* pEvent);

		void UpdateMapView(RECT view);

		void UpdateHorizontalScrollView(int x);
		
		void UpdateVerticalScrollView(int y);

		void SetTileMap(TileMap* tileMap)
		{
			m_tileMap = tileMap;
		}
	};
}
#endif//__TILEMAPCOMPONENT_H__