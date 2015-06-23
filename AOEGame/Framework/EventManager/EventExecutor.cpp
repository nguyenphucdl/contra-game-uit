#include "EventExecutor.h"

namespace Framework
{
	EventExecutor::EventExecutor()
		: m_eventMap(30)
		, m_eventObjectMap(200)
	{

	}

	EventExecutor::~EventExecutor()
	{

	}

	Event*	EventExecutor::_getEvent(EventVector &eventMap, EventID eventId)
	{
		Event* event = NULL;
		try {
			event = eventMap.at(eventId);
		}
		catch (const std::out_of_range& oor) {
			Log::error("Try to get event with event id out of range (%d) reson (%s)", eventId, oor.what());
			throw new GameError(GameErrorNS::FATAL_ERROR, oor.what());
		}
		return event;
	}

	EventVector*	EventExecutor::_getEventVector(ObjectEventVector &eventObjectMap, ObjectId objId)
	{
		EventVector* eventVector = NULL;
		try {
			eventVector = eventObjectMap.at(objId);
		}
		catch (const std::out_of_range& oor) {
			Log::error("Try to get event object with object id out of range (%d) reson (%s)", objId, oor.what());
			throw new GameError(GameErrorNS::FATAL_ERROR, oor.what());
		}
		return eventVector;
	}

	Event*	EventExecutor::_getEvent(EventID eventId)
	{
		return _getEvent(m_eventMap, eventId);
	}

	Event*	EventExecutor::_getExistEvent(EventID eventId)
	{
		Event* event = _getEvent(eventId);
		if (event == NULL)
		{
			Log::error("Try to get event with id not found (%d)", eventId);
			throw new GameError(GameErrorNS::FATAL_ERROR, "Try to get event with id not found");
		}
		return event;
	}

	EventVector*	EventExecutor::_getEventVector(ObjectId objId)
	{
		return _getEventVector(m_eventObjectMap, objId);
	}

	EventVector*	EventExecutor::_getExistEventVector(ObjectId objId)
	{
		EventVector* eventVector = _getEventVector(objId);
		if (eventVector == NULL)
		{
			Log::error("Try to get event object with id not found (%d)", objId);
			throw new GameError(GameErrorNS::FATAL_ERROR, "Try to get event object with id not found");
		}
		return eventVector;
	}

	bool EventExecutor::RegisterEvent(EventID eventId)
	{
		Event* event = _getEvent(eventId);
		if (event == NULL)
		{
			event = new Event(eventId);
			m_eventMap[eventId] = event;
			return true;
		}
		return false;
	}

	void EventExecutor::AttachEvent(EventID eventId, EventHandler& eventHandler)
	{
		RegisterEvent(eventId);
		Event* event = m_eventMap[eventId];
		event->AttachListener(eventHandler);
	}

	void EventExecutor::DetachEvent(EventID eventId, EventHandler& eventHandler)
	{
		Event* event = _getExistEvent(eventId);
		event->DetachListener(eventHandler);
	}

	void EventExecutor::SendEvent(EventID eventId, void* pData)
	{
		//Event* event = _getEvent(eventId);
		//if (event != NULL)
		//{
		//	event->Send(pData);
		//}
		Event* event = m_eventMap[eventId];
		if (event != NULL)
		{
			event->Send(pData);
		}
	}

	void EventExecutor::SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData)
	{
		//Event* event = _getExistEvent(eventId);
		//event->SendToHandler(eventHandler, pData);

		Event* event = m_eventMap[eventId];
		if (event != NULL)
		{
			event->SendToHandler(eventHandler, pData);
		}
	}

	bool EventExecutor::RegisterComponentEvent(EventID eventId, ObjectId objId)
	{
		EventVector* eventObject = _getEventVector(objId);
		if (eventObject == NULL)
		{
			eventObject = new EventVector(100);
			Event* eventOfObject = _getEvent(*eventObject, eventId);
			if (eventOfObject == NULL)
			{
				eventOfObject = new Event(eventId);
				(*eventObject)[eventId] = eventOfObject;
			}
			m_eventObjectMap[objId] = eventObject;
			return true;
		}
		else
		{
			Event* eventOfObject = _getEvent(*eventObject, eventId);
			if (eventOfObject == NULL)
			{
				eventOfObject = new Event(eventId);
				(*eventObject)[eventId] = eventOfObject;
			}
			m_eventObjectMap[objId] = eventObject;
			return true;
		}
		return false;
	}

	void EventExecutor::AttachComponentEvent(EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		RegisterComponentEvent(eventId, objId);
		EventVector* eventObj = m_eventObjectMap[objId];
		Event* event = (*eventObj)[eventId];
		event->AttachListener(eventHandler);
	}

	void EventExecutor::DetachComponentEvent(EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		EventVector* eventObj = _getExistEventVector(objId);
		Event* event = (*eventObj)[objId];
		event->DetachListener(eventHandler);

	}

	void EventExecutor::SendComponentEvent(EventID eventId, ObjectId objId, void* pData)
	{
		/*EventVector* eventObj = _getEventVector(objId);
		if (eventObj != NULL)
		{
			Event* event = (*eventObj)[eventId];
			if (event != NULL)
			{
				event->Send(pData);
			}
		}*/
		Event* event = m_eventObjectMap[objId]->at(eventId);
		if (event != NULL)
		{
			event->Send(pData);
		}
	}

	void EventExecutor::SendComponenEventToHandler(EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData)
	{
		//EventVector* eventObj = _getEventVector(objId);
		//if (eventObj != NULL)
		//{
		//	Event* event = (*eventObj)[eventId];
		//	if (event != NULL)
		//	{
		//		event->SendToHandler(eventHandler, pData);
		//	}
		//}
		Event* event = m_eventObjectMap[objId]->at(eventId);
		if (event != NULL)
		{
			event->SendToHandler(eventHandler, pData);
		}
	}
}