#ifndef __EVENTEXECUTOR_H__
#define __EVENTEXECUTOR_H__

#include "../Application/Context.h"
#include "../Kernel/Task.h"
#include "../GameObjects/GameObject.h"
#include "Event.h"

namespace Framework
{
	typedef std::vector<Event*>						EventVector;
	typedef std::vector<Event*>::iterator			EventVectorIterator;
	typedef std::vector<EventVector*>				ObjectEventVector;
	typedef std::vector<EventVector*>::iterator		ObjectEventVectorIterator;
	class EventExecutor
	{
		friend class Log;

	private:		
		EventVector							m_eventMap;
		ObjectEventVector					m_eventObjectMap;
		

		Event*			_getEvent(EventVector &eventMap, EventID eventId);
		Event*			_getEvent(EventID eventId);
		Event*			_getExistEvent(EventID eventId);
		EventVector*	_getEventVector(ObjectEventVector &eventObjectMap, ObjectId objId);
		EventVector*	_getEventVector(ObjectId objId);
		EventVector*	_getExistEventVector(ObjectId objId);

	public:
		bool RegisterEvent(EventID eventId);
		void AttachEvent(EventID eventId, EventHandler& eventHandler);
		void DetachEvent(EventID eventId, EventHandler& eventHandler);
		void SendEvent(EventID eventId, void* pData);
		void SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData);

		bool RegisterComponentEvent(EventID eventId, ObjectId objId);
		void AttachComponentEvent(EventID eventId, ObjectId objId, EventHandler& eventHandler);
		void DetachComponentEvent(EventID eventId, ObjectId objId, EventHandler& eventHandler);
		void SendComponentEvent(EventID eventId, ObjectId objId, void* pData);
		void SendComponenEventToHandler(EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData);
	public:
		EventExecutor();
		~EventExecutor();
	};
}
#endif