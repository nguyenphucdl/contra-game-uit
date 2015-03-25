﻿#ifndef __ENUMS_H__
#define __ENUMS_H__

namespace Framework
{
	enum Events
	{
		//Main events
		PRE_UPDATE_EVENT,
		UPDATE_EVENT,
		POST_UPDATE_EVENT,
		PRE_RENDER_EVENT,
		RENDER_EVENT,
		POST_RENDER_EVENT,

		//Input events
		KEY_DOWN_EVENT,
		KEY_UP_EVENT
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