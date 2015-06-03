#ifndef __EVENTEXECUTOR_H__
#define __EVENTEXECUTOR_H__

#include "../Application/Context.h"
#include <unordered_map>
#include "../Kernel/Task.h"
#include "EventId.h"
#include "Event.h"

namespace Framework
{
	class EventExecutor
	{
		friend class Log;

	private:
		typedef std::tr1::unordered_map<EventID, Event*>	EventMap;
		typedef EventMap::iterator							EventMapIterator;

		EventMap								m_eventMap;
	public:

		void SendEvent(EventID eventId, void* pData);
		void SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData);
		bool RegisterEvent(EventID eventId);
		void AttachEvent(EventID eventId, EventHandler& eventHandler);
		void DetachEvent(EventID eventId, EventHandler& eventHandler);

	public:
		EventExecutor();
		~EventExecutor();
	};
}
#endif