#include "EventExecutor.h"

namespace Framework
{
	EventExecutor::EventExecutor()
	{
		
	}

	EventExecutor::~EventExecutor()
	{
		for (EventMapIterator iter = m_eventMap.begin(); iter != m_eventMap.end(); ++iter)
		{
			Event* pEvent = iter->second;
			if (pEvent)
			{
				delete pEvent;
				iter->second = NULL;
			}
		}

		m_eventMap.clear();

		for (ObjectMapIterator iter = m_eventObjectMap.begin(); iter != m_eventObjectMap.end(); ++iter)
		{
			EventMap* pEventMap = iter->second;
			if (pEventMap)
			{
				for (EventMapIterator iiter = pEventMap->begin(); iiter != pEventMap->end(); ++iiter)
				{
					Event* pEvent = iiter->second;
					if (pEvent)
					{
						delete pEvent;
						iiter->second = NULL;
					}
				}
				pEventMap->clear();
				delete pEventMap;
				iter->second = NULL;
			}
		}
		m_eventObjectMap.clear();
	}

	void EventExecutor::SendEvent(EventID eventId, void* pData)
	{
		EventMapIterator result = m_eventMap.find(eventId);
		if (result != m_eventMap.end())
		{
			assert(result->second);
			if (result->second)
			{
				result->second->Send(pData);
			}
		}
	}

	void EventExecutor::SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData)
	{
		EventMapIterator result = m_eventMap.find(eventId);
		if (result != m_eventMap.end())
		{
			assert(result->second);
			if (result->second)
			{
				result->second->SendToHandler(eventHandler, pData);
			}
		}
	}

	void EventExecutor::SendEventToHandler(EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData)
	{
		ObjectMapIterator objIt = m_eventObjectMap.find(objId);
		assert(objIt != m_eventObjectMap.end());
		if (objIt != m_eventObjectMap.end())
		{
			assert(objIt->second);
			EventMap* eventMap = objIt->second;
			EventMapIterator eventMapIt = eventMap->find(eventId);
			assert(eventMapIt != eventMap->end());
			if (eventMapIt != eventMap->end())
			{
				assert(eventMapIt->second);
				eventMapIt->second->SendToHandler(eventHandler, pData);
			}
		}
	}

	//NEW
	void EventExecutor::SendEvent(EventID eventId, ObjectId objId, void* pData)
	{


		ObjectMapIterator objIt = m_eventObjectMap.find(objId);
		if (objIt != m_eventObjectMap.end())
		{
			assert(objIt->second);
			EventMap* eventMap = objIt->second;
			EventMapIterator eventMapIt = eventMap->find(eventId);
			if (eventMapIt != eventMap->end())
			{
				assert(eventMapIt->second);
				eventMapIt->second->Send(pData);
			}
		}
	}
	//NEW
	void EventExecutor::DetachEvent(EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		ObjectMapIterator objIt = m_eventObjectMap.find(objId);
		assert(objIt != m_eventObjectMap.end());
		if (objIt != m_eventObjectMap.end())
		{
			assert(objIt->second);
			EventMap* eventMap = objIt->second;
			EventMapIterator eventMapIt = eventMap->find(eventId);
			assert(eventMapIt != eventMap->end());
			if (eventMapIt != eventMap->end())
			{
				assert(eventMapIt->second);
				eventMapIt->second->DetachListener(eventHandler);
			}
		}
	}

	//NEW
	void EventExecutor::AttachEvent(EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		ObjectMapIterator objIt = m_eventObjectMap.find(objId);
		assert(objIt != m_eventObjectMap.end());
		if (objIt != m_eventObjectMap.end())
		{
			assert(objIt->second);
			EventMap* eventMap = objIt->second;
			EventMapIterator eventMapIt = eventMap->find(eventId);
			assert(eventMapIt != eventMap->end());
			if (eventMapIt != eventMap->end())
			{
				assert(eventMapIt->second);
				eventMapIt->second->AttachListener(eventHandler);
			}
		}
	}

	//NEW
	bool EventExecutor::RegisterEvent(EventID evenId, ObjectId objId)
	{
		bool added = false;

		ObjectMapIterator objIt = m_eventObjectMap.find(objId);
		if (objIt == m_eventObjectMap.end())
		{
			EventMap* pNewEventMap = new EventMap();
			Event* pNewEvent = new Event(evenId);
			if (pNewEventMap && pNewEvent)
			{
				std::pair<EventID, Event*> newEvent(evenId, pNewEvent);
				std::pair<EventMapIterator, bool> addedIter = pNewEventMap->insert(newEvent);
				added = addedIter.second;

				if (added)
				{
					std::pair<ObjectId, EventMap*> newEventMap(objId, pNewEventMap);
					std::pair<ObjectMapIterator, bool> addedMapIter = m_eventObjectMap.insert(newEventMap);
					added = addedMapIter.second;
				}
			}
		}
		else
		{
			EventMap* pEventMap = objIt->second;
			EventMapIterator eventMapIt = pEventMap->find(evenId);
			if (eventMapIt == pEventMap->end())
			{
				Event* pNewEvent = new Event(evenId);
				std::pair<EventID, Event*> newEvent(evenId, pNewEvent);
				std::pair<EventMapIterator, bool> addedIter = pEventMap->insert(newEvent);
				added = addedIter.second;
			}
		}
		return added;
	}

	bool EventExecutor::RegisterEvent(EventID eventId)
	{
		bool added = false;

		EventMapIterator result = m_eventMap.find(eventId);
		if (result == m_eventMap.end())
		{
			Event* pNewEvent = new Event(eventId);

			if (pNewEvent)
			{
				std::pair<EventID, Event*> newEvent(eventId, pNewEvent);
				std::pair<EventMapIterator, bool> addedIter = m_eventMap.insert(newEvent);
				added = addedIter.second;
			}
		}

		//assert(added);
		return added;
	}

	void EventExecutor::AttachEvent(EventID eventId, EventHandler& eventHandler)
	{
		EventMapIterator result = m_eventMap.find(eventId);
		assert(result != m_eventMap.end());
		if (result != m_eventMap.end())
		{
			assert(result->second);
			result->second->AttachListener(eventHandler);
		}
	}

	void EventExecutor::DetachEvent(EventID eventId, EventHandler& eventHandler)
	{
		EventMapIterator result = m_eventMap.find(eventId);
		assert(result != m_eventMap.end());
		if (result != m_eventMap.end())
		{
			assert(result->second);
			result->second->DetachListener(eventHandler);
		}
	}
}