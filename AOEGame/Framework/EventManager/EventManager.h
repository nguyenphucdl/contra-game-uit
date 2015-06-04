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
		friend void SendEventAdvanced(EventID eventId, ObjectId objId, void* pData);
		friend void SendEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, void* pData);
		friend void SendEventToHandler(EventID eventId, EventHandler& eventHandler, void *pData);
		friend void SendEventToHandler(ExecutorID execId, EventID eventId, EventHandler& eventHandler, void *pData);
		friend void SendEventToHandlerAdvanced(EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData);
		friend void SendEventToHandlerAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData);
		friend bool RegisterEvent(EventID eventId);
		friend bool RegisterEvent(ExecutorID execId, EventID eventId);
		friend bool RegisterEventAdvanced(EventID eventId, ObjectId objId);
		friend bool RegisterEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId);
		friend void AttachEvent(EventID eventId, EventHandler& eventHandler);
		friend void AttachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler);
		friend void AttachEventAdvanced(EventID eventId, ObjectId objId, EventHandler& eventHandler);
		friend void AttachEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler);
		friend void DetachEvent(EventID eventId, EventHandler& eventHandler);
		friend void DetachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler);
		friend void DetachEventAdvanced(EventID eventId, ObjectId objId, EventHandler& eventHandler);
		friend void DetachEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler);
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
		void SendEventAdvanced(EventID eventId, ObjectId objId, void* pData);
		void SendEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, void* pData);
		void SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData);
		void SendEventToHandler(ExecutorID execId, EventID eventId, EventHandler& eventHandler, void* pData);
		void SendEventToHandlerAdvanced(EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData);
		void SendEventToHandlerAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData);
		bool RegisterEvent(EventID eventId);
		bool RegisterEvent(ExecutorID execId, EventID eventId);
		bool RegisterEventAdvanced(EventID eventId, ObjectId objId);
		bool RegisterEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId);
		void AttachEvent(EventID eventId, EventHandler& eventHandler);
		void AttachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler);
		void AttachEventAdvanced(EventID eventId, ObjectId objId, EventHandler& eventHandler);
		void AttachEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler);
		void DetachEvent(EventID eventId, EventHandler& eventHandler);
		void DetachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler);
		void DetachEventAdvanced(EventID eventId, ObjectId objId, EventHandler& eventHandler);
		void DetachEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler);
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

	inline void SendEventAdvanced(EventID eventId, ObjectId objId, void* pData)
	{
		SendEventAdvanced(EventManager::GetSingletonPtr()->GetActiveExecutor(), eventId, objId, pData);
	}

	inline void SendEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, void* pData)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SendEventAdvanced(execId, eventId, objId, pData);
		}
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

	inline void SendEventToHandlerAdvanced(EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData)
	{
		SendEventToHandlerAdvanced(EventManager::GetSingletonPtr()->GetActiveExecutor(), eventId, objId, eventHandler, pData);
	}

	inline void SendEventToHandlerAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SendEventToHandlerAdvanced(execId, eventId, objId, eventHandler, pData);
		}
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

	inline bool RegisterEventAdvanced(EventID eventId, ObjectId objId)
	{
		return RegisterEventAdvanced(EventManager::GetSingletonPtr()->GetActiveExecutor(), eventId, objId);
	}

	inline bool RegisterEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			return pEventManager->RegisterEventAdvanced(execId, eventId, objId);
		}
		return false;
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
		AttachEvent(EventManager::GetSingletonPtr()->GetActiveExecutor(), eventId, eventHandler);
	}

	inline void AttachEventAdvanced(EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		AttachEventAdvanced(EventManager::GetSingletonPtr()->GetActiveExecutor(), eventId, objId, eventHandler);
	}

	inline void AttachEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		RegisterEventAdvanced(execId, eventId, objId);
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->AttachEventAdvanced(execId, eventId, objId, eventHandler);
		}
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

	inline void DetachEventAdvanced(EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		DetachEventAdvanced(EventManager::GetSingletonPtr()->GetActiveExecutor(), eventId, objId, eventHandler);
	}

	inline void DetachEventAdvanced(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->DetachEventAdvanced(execId, eventId, objId, eventHandler);
		}
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
