﻿#ifndef __ENUMS_H__
#define __ENUMS_H__

namespace Framework
{
	enum Events
	{
		//System events
		SYS_PRE_RENDER_EVENT,
		SYS_RENDER_EVENT,
		SYS_POST_RENDER_EVENT,
		SYS_KEY_UP_EVENT,
		SYS_KEY_DOWN_EVENT,

		//Scene Events
		SCE_PRE_RENDER_EVENT,
		SCE_RENDER_EVENT,
		SCE_POST_RENDER_EVENT,
		SCE_PRE_UPDATE_EVENT,
		SCE_UPDATE_EVENT,
		SCE_POST_UPDATE_EVENT,
		SCE_KEY_UP_EVENT,
		SCE_KEY_DOWN_EVENT,
		
		SCE_COLLISION_EVENT,
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
		BulletComponentId,
		LifeTimeComponentId,
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
		JUMP_FIRING= 450,
	};

	enum BulletStates
	{
		FIRE = 100,
		EXPLODE = 200
	};

	enum ExecutorIDs
	{
		SysRender,
		SysInput,
		GamePlayId,


		Chapter6TaskId,//Test
		GamePlay1Id
	};
}
#endif