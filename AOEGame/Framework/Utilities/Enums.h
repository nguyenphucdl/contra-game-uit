#ifndef __ENUMS_H__
#define __ENUMS_H__

namespace Framework
{
	enum Events
	{
		//Main events
		PRE_UPDATE_EVENT,	// UNUSED
		UPDATE_EVENT,		// UNUSED
		POST_UPDATE_EVENT,	// UNUSED
		PRE_RENDER_EVENT,
		RENDER_EVENT,		// UNUSED
		POST_RENDER_EVENT,	// UNUSED

		//Input events
		KEY_DOWN_EVENT,		// Fire from Input task
		KEY_UP_EVENT		// Fire form Input task
	};

	enum GameEvents
	{
		PLAYER_JUMP_EVENT,
	};

	enum ComponentIDs
	{
		//Common Components
		RenderableComponentId,
		TransformComponentId,

		//Game Components
		CameraComponentId,
		SpriteComponentId,
		TileMapComponentId,
		MovementComponentId,
		StaticComponentId
	};
}
#endif