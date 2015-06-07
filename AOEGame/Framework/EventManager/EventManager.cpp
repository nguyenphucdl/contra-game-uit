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

	void EventManager::SendEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, void* pData)
	{
		EventExecutorMapIterator result = m_eventExecutorMap.find(execId);
		if (result != m_eventExecutorMap.end())
		{
			assert(result->second);
			EventExecutor* executor = result->second;
			executor->SendEvent(eventId, objId, pData);
		}
	}

	void EventManager::SendEventAdvanced(EventID eventId, ObjectId objId, void* pData)
	{
		SendEventAdvanced(GetActiveExecutor(), eventId, objId, pData);
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

	void EventManager::SendEventToHandlerAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData)
	{
		EventExecutorMapIterator result = m_eventExecutorMap.find(execId);
		if (result != m_eventExecutorMap.end())
		{
			assert(result->second);
			EventExecutor* executor = result->second;
			executor->SendEventToHandler(eventId, objId, eventHandler, pData);
		}
	}

	void EventManager::SendEventToHandlerAdvanced(EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData)
	{
		SendEventToHandlerAdvanced(GetActiveExecutor(), eventId, objId, eventHandler, pData);
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

	bool EventManager::RegisterEventAdvanced(EventID eventId, ObjectId objId)
	{
		return RegisterEventAdvanced(GetActiveExecutor(), eventId, objId);
	}

	bool EventManager::RegisterEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId)
	{
		bool added = false;
		EventExecutorMapIterator result = m_eventExecutorMap.find(execId);
		if (result == m_eventExecutorMap.end())
		{
			EventExecutor* pNewExecutor = new EventExecutor();
			pNewExecutor->RegisterEvent(eventId, objId);

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
			return executor->RegisterEvent(eventId, objId);
		}
		return added;
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

	void EventManager::AttachEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		EventExecutorMapIterator result = m_eventExecutorMap.find(execId);
		if (result != m_eventExecutorMap.end())
		{
			assert(result->second);
			EventExecutor* executor = result->second;
			executor->AttachEvent(eventId, objId, eventHandler);
		}
	}

	void EventManager::AttachEventAdvanced(EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		AttachEventAdvanced(GetActiveExecutor(), eventId, objId, eventHandler);
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

	void EventManager::DetachEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		EventExecutorMapIterator result = m_eventExecutorMap.find(execId);
		if (result != m_eventExecutorMap.end())
		{
			assert(result->second);
			EventExecutor* executor = result->second;
			executor->DetachEvent(eventId, objId, eventHandler);
		}
	}

	void EventManager::DetachEventAdvanced(EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		DetachEventAdvanced(GetActiveExecutor(), eventId, objId, eventHandler);
	}
	
}
