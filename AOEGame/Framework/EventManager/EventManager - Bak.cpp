#include "EventManager.h"

namespace Framework
{
	EventManager::EventManager()
	{
		
	}

	EventManager::~EventManager()
	{
		for (EventExecutorMapIterator iter = m_eventExecutorMap.begin(); iter != m_eventExecutorMap.end(); ++iter)
		{
			EventExecutor* pExec = iter->second;
			if (pExec)
			{
				delete pExec;
				iter->second = NULL;
			}
		}

		m_eventExecutorMap.clear();
	}

	ExecutorID EventManager::GetActiveExecutor()
	{
		return m_activeExecutorId;
	}

	void EventManager::SendEvent(ExecutorID execId, EventID eventId, void* pData)
	{
		EventExecutorMapIterator result = m_eventExecutorMap.find(execId);
		if (result != m_eventExecutorMap.end())
		{
			assert(result->second);
			EventExecutor* executor = result->second;
			executor->SendEvent(eventId, pData);
		}
	}

	void EventManager::SendEvent(EventID eventId, void* pData)
	{
		SendEvent(GetActiveExecutor(), eventId, pData);
	}

	void EventManager::SendEventToHandler(ExecutorID execId, EventID eventId, EventHandler& eventHandler, void* pData)
	{
		EventExecutorMapIterator result = m_eventExecutorMap.find(execId);
		if (result != m_eventExecutorMap.end())
		{
			assert(result->second);
			EventExecutor* executor = result->second;
			executor->SendEventToHandler(eventId, eventHandler, pData);
		}
	}

	void EventManager::SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData)
	{
		SendEventToHandler(GetActiveExecutor(), eventId, eventHandler, pData);
	}

	bool EventManager::RegisterEvent(ExecutorID execId, EventID eventId)
	{
		bool added = false;
		EventExecutorMapIterator result = m_eventExecutorMap.find(execId);
		if (result == m_eventExecutorMap.end())
		{
			EventExecutor* pNewExecutor = new EventExecutor();
			pNewExecutor->RegisterEvent(eventId);

			if (pNewExecutor)
			{
				std::pair<ExecutorID, EventExecutor*> newExec(execId, pNewExecutor);
				std::pair<EventExecutorMapIterator, bool> addedIter = m_eventExecutorMap.insert(newExec);
				added = addedIter.second;
			}
		}
		else
		{
			assert(result->second);
			EventExecutor* executor = result->second;
			return executor->RegisterEvent(eventId);
		}
		return added;
	}

	bool EventManager::RegisterEvent(EventID eventId)
	{
		return RegisterEvent(GetActiveExecutor(), eventId);
	}

	void EventManager::AttachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler)
	{
		EventExecutorMapIterator result = m_eventExecutorMap.find(execId);
		if (result != m_eventExecutorMap.end())
		{
			assert(result->second);
			EventExecutor* executor = result->second;
			executor->AttachEvent(eventId, eventHandler);
		}
	}

	void EventManager::AttachEvent(EventID eventId, EventHandler& eventHandler)
	{
		AttachEvent(GetActiveExecutor(), eventId, eventHandler);
	}

	void EventManager::DetachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler)
	{
		EventExecutorMapIterator result = m_eventExecutorMap.find(execId);
		if (result != m_eventExecutorMap.end())
		{
			assert(result->second);
			EventExecutor* executor = result->second;
			executor->DetachEvent(eventId, eventHandler);
		}
	}

	void EventManager::DetachEvent(EventID eventId, EventHandler& eventHandler)
	{
		DetachEvent(GetActiveExecutor(), eventId, eventHandler);
	}
	
}
