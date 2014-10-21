#ifndef __EVENTID_H__
#define __EVENTID_H__

namespace Framework
{
	class GameObject;

	typedef unsigned int EventID;

	static const EventID UPDATE_EVENT		= 0;
	static const EventID POSTUPDATE_EVENT	= 1;
	static const EventID RENDER_EVENT		= 2;
	static const EventID JUMP_EVENT			= 3;
	static const EventID COLLISION_EVENT	= 4;
	static const EventID PAUSEAPP_EVENT		= 5;
	static const EventID RESUMEAPP_EVENT	= 6;
	static const EventID PLAYERJUMP_EVENT	= 7;
	static const EventID KEYDOWN_EVENT		= 8; // Test
	static const EventID KEYUP_EVENT		= 9;

	struct CollisionEventData
	{
		GameObject* m_pCollider;
	};

}
#endif