#ifndef __ENUMS_H__
#define __ENUMS_H__

namespace Framework
{
	enum Events
	{
		//Main events
		PRE_UPDATE_EVENT = 3,	// UNUSED
		UPDATE_EVENT,		// UNUSED
		POST_UPDATE_EVENT,	// UNUSED
		PRE_RENDER_EVENT,
		RENDER_EVENT,		// UNUSED
		POST_RENDER_EVENT,	// UNUSED
		COLLISION_EVENT,

		//Input events
		KEY_DOWN_EVENT,		// Fire from Input task
		KEY_UP_EVENT,		// Fire form Input task
		PLAYER_JUMP_EVENT
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
		StaticComponentId,
		CollisionComponentId,

		//Player Components
		PlayerMovementComponentId
	};

	enum SpriteDirections
	{
		LEFT = 0,
		RIGHT = 1,
		UP = 2,
		DOWN = 4
	};

	enum SpriteStates
	{
		STATIONARY = 100,
		STATIONARY_FIRING = 150,
		MOVE = 200,
		MOVE_FIRING = 250,
		SIT = 300,
		JUMP = 400,
		JUMP_FIRING= 450
	};

}
#endif