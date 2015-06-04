#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include "../Application/Context.h"
#include "../Kernel/Task.h"
#include "EventId.h"
#include "Event.h"
#include "EventExecutor.h"
#include "EventExecutorAware.h"
#include "../GameObjects/Component.h"

namespace Framework
{
	class EventManager
		: public Singleton<EventManager>
	{
		friend void SendEvent(EventID eventId, void* pData);
		friend void SendEvent(ExecutorID execId, EventID eventId, void* pData);
		friend void SendEventToHandler(EventID eventId, EventHandler& eventHandler, void *pData);
		friend void SendEventToHandler(ExecutorID execId, EventID eventId, EventHandler& eventHandler, void *pData);
		friend bool RegisterEvent(EventID eventId);
		friend bool RegisterEvent(ExecutorID execId, EventID eventId);
		friend void AttachEvent(EventID eventId, EventHandler& eventHandler);
		//friend void AttachEventAdvanced(EventID eventId, GameObject& obj);
		friend void AttachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler);
		friend void DetachEvent(EventID eventId, EventHandler& eventHandler);
		friend void DetachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler);
		friend void SetExecutorId(ExecutorID execId);
		friend void SetExecutor(EventExecutorAware* exec);
		friend class Log;

	private:
		typedef std::tr1::unordered_map<ExecutorID, EventExecutor*>			EventExecutorMap;
		typedef EventExecutorMap::iterator									EventExecutorMapIterator;

		EventExecutorMap						m_eventExecutorMap;

		ExecutorID								m_activeExecutorId;
		ExecutorID GetActiveExecutor();

		void SendEvent(EventID eventId, void* pData);
		void SendEvent(ExecutorID execId, EventID eventId, void* pData);
		void SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData);
		void SendEventToHandler(ExecutorID execId, EventID eventId, EventHandler& eventHandler, void* pData);
		bool RegisterEvent(EventID eventId);
		bool RegisterEvent(ExecutorID execId, EventID eventId);
		void AttachEvent(EventID eventId, EventHandler& eventHandler);
		void AttachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler);
		void DetachEvent(EventID eventId, EventHandler& eventHandler);
		void DetachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler);
		void SetExecutorId(ExecutorID execId) { m_activeExecutorId = execId; }
		void SetEXecutor(EventExecutorAware* exec) { SetExecutorId(exec->GetExecutorId()); };
	public:
		EventManager();
		~EventManager();
	};

	inline void SendEvent(ExecutorID execId, EventID eventId, void* pData = NULL)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SendEvent(execId, eventId, pData);
		}
	}

	inline void SendEvent(EventID eventId, void* pData = NULL)
	{
		SendEvent(EventManager::GetSingletonPtr()->GetActiveExecutor(), eventId, pData);
	}

	inline void SendEventToHandler(ExecutorID execId, EventID eventId, EventHandler& eventHandler, void *pData = NULL)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SendEventToHandler(execId, eventId, eventHandler, pData);
		}
	}

	inline void SendEventToHandler(EventID eventId, EventHandler& eventHandler, void *pData = NULL)
	{
		SendEventToHandler(EventManager::GetSingletonPtr()->GetActiveExecutor(), eventId, eventHandler, pData);
	}

	inline bool RegisterEvent(ExecutorID execId, EventID eventId)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			return pEventManager->RegisterEvent(execId, eventId);
		}
		return false;
	}

	inline bool RegisterEvent(EventID eventId)
	{
		return RegisterEvent(EventManager::GetSingletonPtr()->GetActiveExecutor(), eventId);
	}

	inline void AttachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler)
	{
		RegisterEvent(execId, eventId);
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->AttachEvent(execId, eventId, eventHandler);
		}
	}

	inline void AttachEvent(EventID eventId, EventHandler& eventHandler)
	{
		RegisterEvent(EventManager::GetSingletonPtr()->GetActiveExecutor(), eventId);
		AttachEvent(EventManager::GetSingletonPtr()->GetActiveExecutor(), eventId, eventHandler);
	}

	inline void DetachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->DetachEvent(execId, eventId, eventHandler);
		}
	}

	inline void DetachEvent(EventID eventId, EventHandler& eventHandler)
	{
		DetachEvent(EventManager::GetSingletonPtr()->GetActiveExecutor(), eventId, eventHandler);
	}

	inline void SetExecutorId(ExecutorID execId)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SetExecutorId(execId);
		}
	}

	inline void SetExecutor(EventExecutorAware* exec)
	{
		SetExecutorId(exec->GetExecutorId());
	}
}

#endif//__EVENTMANAGER_H__
