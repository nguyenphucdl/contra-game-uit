#ifndef __EVENTEXECUTOR_H__
#define __EVENTEXECUTOR_H__

#include "../Application/Context.h"
#include "../Kernel/Task.h"
#include "../GameObjects/GameObject.h"
#include "EventId.h"
#include "Event.h"

namespace Framework
{
	class EventExecutor
	{
		friend class Log;

	private:
		typedef std::tr1::unordered_map<EventID, Event*>			EventMap;
		typedef EventMap::iterator									EventMapIterator;
		typedef std::tr1::unordered_map<ObjectId, EventMap*>		ObjectMap;
		typedef ObjectMap::iterator									ObjectMapIterator;

		EventMap							m_eventMap;

		ObjectMap							m_eventObjectMap;
		

	public:

		void SendEvent(EventID eventId, void* pData);
		void SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData);
		bool RegisterEvent(EventID eventId);
		void AttachEvent(EventID eventId, EventHandler& eventHandler);
		void DetachEvent(EventID eventId, EventHandler& eventHandler);

		//Advanced
		bool RegisterEvent(EventID eventId, ObjectId objId);
		void AttachEvent(EventID eventId, ObjectId objId, EventHandler& eventHandler);
		void DetachEvent(EventID eventId, ObjectId objId, EventHandler& eventHandler);
		void SendEvent(EventID eventId, ObjectId objId, void* pData);
		void SendEventToHandler(EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData);
	public:
		EventExecutor();
		~EventExecutor();
	};
}
#endif