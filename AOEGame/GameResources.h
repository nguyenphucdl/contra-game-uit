#ifndef __GAME_RESOURCES_H__
#define __GAME_RESOURCES_H__

namespace GameResources
{
	const char ROCKMAN_CLIMBING_FIRING[] = "rockman-climbing-firing.png";
	const char ROCKMAN_FALLING[] = "rockman-falling.png";
	const char ROCKMAN_JUMPING[] = "rockman-jumping.png";
	const char ROCKMAN_RUNNING_FIRING[] = "rockman-running-firing.png";
	const char ROCKMAN_RUNNING[] = "rockman-running.png";
	const char ROCKMAN_STATIONARY[] = "rockman-stationary.png";
	const char ROCKMAN_CLIMBING[] = "rockman-climbing.png";
	const char ROCKMAN_BULLET_FIRING[] = "rockman_bullet.png";
	const char HEALTH__BACKGROUND_BAR[] = "health-background-vertical.png";
	const char ROCKMAN_HEALTH_BAR[] = "bar_rockman_vertical.png";



	const char MAP1_NPC_LITTLEPOLYGOT[] = "littlepolygot.png";
	const char MAP1_NPC_NAPALMBOMB[] = "napalmbomb.png";
	const char MAP1_FIVESTARSHOOTER[] = "fivestarshooter.png";
	const char MAP1_NPC_WALL_SHOOTER[] = "wallshooter.png";
	const char MAP1_NPC_GREEN_ROBOCOP[] = "greenrobocap.png";
	const char MAP1_NPC_BOSS_BOMBMAN[] = "bossbombman.png";
	const char MAP1_NPC_BULLET_BILL[] = "";
	const char MAP1_NPC_FLOOR_TRAPPER[] = "";
	const char MAP1_BOMMAN_HEALTH_BAR[] = "boomman-health-vertical.png";
	const char MAP1_BACKGROUND_HEALTH_BAR[] = "health-background-vertical.png";

	enum GameObjectTypes 
	{
		LITTLE_POGOBOT = 1000,
		NAPALM_BOMB = 1001,
		FIVE_STAR_SHOOTER = 1002,
		WALL_SHOOTER = 1003,
		GREEN_ROBOCOP = 1004,
		BULLET_BILL = 1005,
		FLOOR_TRAPPER = 1006,
		BOSS_BOMBMAN = 1007,

		PLAYER_OBJECT = Framework::SystemObjectTypes::PLAYER_OBJECT,
		TILEMAP_OBJECT = Framework::SystemObjectTypes::TILEMAP_OBJECT,
		CAMERA_OBJECT = Framework::SystemObjectTypes::CAMERA_OBJECT,

		PLAYER_BULLET = Framework::SystemObjectTypes::PLAYER_BULLET,
		NPC_BULLET = Framework::SystemObjectTypes::NPC_BULLET
	};

	const float CONST_SPRITE_ANIMATION_TIME = 1.5f;
	const float CONST_CLIMBING_ANIMATION_TIME = 1.5f;
	const float CONST_BULLET_VELOCITY_X = 400.0f;
	const float CONST_BULLET_VELOCITY_Y = 0.f;
	const float CONST_BULLET_LIFETIME = 3.0f;
	const float CONST_BULLET_DELAY_TIME = 0.25f;
};

#endif//__GAME_RESOURCES_H__