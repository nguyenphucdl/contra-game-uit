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