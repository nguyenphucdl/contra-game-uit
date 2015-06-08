#include "EventManager.h"

namespace Framework
{
	EventManager::EventManager()
		: m_activeExecutorId(-1)
		, m_eventExecutorVector(30)
	{
		
	}

	EventManager::~EventManager()
	{
		for (EventExecutorVectorIterator it = m_eventExecutorVector.begin(); it != m_eventExecutorVector.end(); it++)
		{
			EventExecutor* eventExecutor = *it;
			delete eventExecutor;
		}
		m_eventExecutorVector.clear();
	}

	EventExecutor*	EventManager::_getEventExecutor(ExecutorID execId)
	{
		EventExecutor* eventExecutor = NULL;
		try {
			eventExecutor = m_eventExecutorVector.at(execId);
		}
		catch (const std::out_of_range& oor) {
			Log::error("Try to register event with id out of range (%d) reson (%s)", execId, oor.what());
			throw new GameError(GameErrorNS::FATAL_ERROR, oor.what());
		}
		return eventExecutor;
	}

	void	EventManager::AttachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler)
	{
		EventExecutor* eventExecutor = _getEventExecutor(execId);
		if (eventExecutor == NULL)
		{
			eventExecutor = new EventExecutor();
			m_eventExecutorVector[execId] = eventExecutor;
		}
		eventExecutor->AttachEvent(eventId, eventHandler);
	}

	void	EventManager::AttachEvent(EventID eventId, EventHandler& eventHandler)
	{
		AttachEvent(m_activeExecutorId, eventId, eventHandler);
	}
	
	void	EventManager::SendEvent(ExecutorID execId, EventID eventId, void* pData)
	{
		EventExecutor* executor = _getEventExecutor(execId);
		if (executor != NULL)
		{
			executor->SendEvent(eventId, pData);
		}
	}

	void	EventManager::SendEvent(EventID eventId, void* pData)
	{
		SendEvent(m_activeExecutorId, eventId, pData);
	}

	void	EventManager::SendEventToHandler(ExecutorID execId, EventID eventId, EventHandler& eventHandler, void* pData)
	{
		EventExecutor* executor = _getEventExecutor(execId);
		if (executor != NULL)
		{
			executor->SendEventToHandler(eventId, eventHandler, pData);
		}
	}

	void	EventManager::SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData)
	{
		SendEventToHandler(m_activeExecutorId, eventId, eventHandler, pData);
	}

	void	EventManager::AttachComponentEvent(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		EventExecutor* eventExecutor = _getEventExecutor(execId);
		if (eventExecutor == NULL)
		{
			eventExecutor = new EventExecutor();
			m_eventExecutorVector[execId] = eventExecutor;
		}
		eventExecutor->AttachComponentEvent(eventId, objId, eventHandler);
	}

	void	EventManager::AttachComponentEvent(EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		AttachComponentEvent(m_activeExecutorId, eventId, objId, eventHandler);
	}

	void	EventManager::SendComponentEvent(ExecutorID execId, EventID eventId, ObjectId objId, void* pData)
	{
		EventExecutor* executor = _getEventExecutor(execId);
		if (executor != NULL)
		{
			executor->SendComponentEvent(eventId, objId, pData);
		}
	}

	void	EventManager::SendComponentEvent(EventID eventId, ObjectId objId, void* pData)
	{
		SendComponentEvent(m_activeExecutorId, eventId, objId, pData);
	}

	void	EventManager::SendComponentEventToHandler(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData)
	{
		EventExecutor* executor = _getEventExecutor(execId);
		if (executor != NULL)
		{
			executor->SendComponenEventToHandler(eventId, objId, eventHandler, pData);
		}
	}

	void	EventManager::SendComponentEventToHandler(EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData)
	{
		SendComponentEventToHandler(m_activeExecutorId, eventId, objId, eventHandler, pData);
	}
}
