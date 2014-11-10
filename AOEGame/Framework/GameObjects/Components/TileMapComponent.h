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

namespace Framework
{
	class TileMapComponent
		: public Component
		, public EventHandler
	{
	private:
		static const unsigned int s_id = 3;

		TileMap*				m_tileMap;		

		bool					m_initilize;

	public:
		static unsigned int GetId() { return s_id; }

		explicit TileMapComponent(GameObject* pOwner);
		virtual ~TileMapComponent();

		virtual void Initialize();

		virtual void HandleEvent(Event* pEvent);

		void SetTileMap(TileMap* tileMap)
		{
			m_tileMap = tileMap;
		}
	};
}
#endif//__TILEMAPCOMPONENT_H__