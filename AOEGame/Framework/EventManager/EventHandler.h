#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

namespace Framework
{
	class Event;

	class EventHandler
	{
	public:
		virtual ~EventHandler() {}

		virtual void HandleEvent(Event* pEvent) = 0;
	};
}
#endif//__EVENTHANDLER_H__