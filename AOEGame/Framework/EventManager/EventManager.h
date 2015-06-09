#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include "../Application/Context.h"
#include "../Kernel/Task.h"
#include "Event.h"
#include "EventExecutor.h"
#include "EventExecutorAware.h"
#include "../GameObjects/Component.h"

namespace Framework
{
	class EventManager
		: public Singleton < EventManager >
	{
		friend void				SetActiveExecutorId(ExecutorID id);
		friend void				SetActiveExecutor(EventExecutorAware* owner);

		friend void				AttachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler);
		friend void				AttachEvent(EventID eventId, EventHandler& eventHandler);
		friend void				SendEvent(ExecutorID execId, EventID eventId, void* pData = NULL);
		friend void				SendEvent(EventID eventId, void* pData = NULL);
		friend void				SendEventToHandler(ExecutorID execId, EventID eventId, EventHandler& eventHandler, void* pData);
		friend void				SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData);
		friend void				BroadcastComponentEvent(EventID eventId, std::vector<GameObject*>* objects, void* pData);

		friend void				AttachComponentEvent(ExecutorID execId, EventID eventId, GameObject* obj, EventHandler& eventHandler);
		friend void				AttachComponentEvent(EventID eventId, GameObject* obj, EventHandler& eventHandler);
		friend void				SendComponentEvent(ExecutorID execId, EventID eventId, GameObject* obj, void* pData = NULL);
		friend void				SendComponentEvent(EventID eventId, GameObject* obj, void* pData = NULL);
		friend void				SendComponentEventToHandler(ExecutorID execId, EventID eventId, GameObject* obj, EventHandler& eventHandler, void* pData);
		friend void				SendComponentEventToHandler(EventID eventId, GameObject* obj, EventHandler& eventHandler, void* pData);
		friend class Log;

	private:
		typedef std::vector<EventExecutor*>			EventExecutorVector;
		typedef EventExecutorVector::iterator		EventExecutorVectorIterator;

		EventExecutorVector							m_eventExecutorVector;
		ExecutorID									m_activeExecutorId;

		EventExecutor*		_getEventExecutor(ExecutorID execId);
	public:
		EventManager();
		~EventManager();

		ExecutorID			GetActiveExecutor(){ return m_activeExecutorId; }
		void				SetActiveExecutorId(ExecutorID id) { m_activeExecutorId = id; }
		void				SetActiveExecutor(EventExecutorAware* owner) { m_activeExecutorId = owner->GetExecutorId(); }

		void				AttachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler);
		void				AttachEvent(EventID eventId, EventHandler& eventHandler);
		void				SendEvent(ExecutorID execId, EventID eventId, void* pData);
		void				SendEvent(EventID eventId, void* pData);
		void				SendEventToHandler(ExecutorID execId, EventID eventId, EventHandler& eventHandler, void* pData);
		void				SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData);


		void				AttachComponentEvent(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler);
		void				AttachComponentEvent(EventID eventId, ObjectId objId, EventHandler& eventHandler);
		void				SendComponentEvent(ExecutorID execId, EventID eventId, ObjectId objId, void* pData);
		void				SendComponentEvent(EventID eventId, ObjectId objId, void* pData);
		void				SendComponentEventToHandler(ExecutorID execId, EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData);
		void				SendComponentEventToHandler(EventID eventId, ObjectId objId, EventHandler& eventHandler, void* pData);
	};

	inline void				SetActiveExecutorId(ExecutorID id)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		if (pEventManager)
		{
			pEventManager->SetActiveExecutorId(id);
		}
	}
	inline void				SetActiveExecutor(EventExecutorAware* owner)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SetActiveExecutor(owner);
		}
	}
	inline void				AttachEvent(ExecutorID execId, EventID eventId, EventHandler& eventHandler)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->AttachEvent(execId, eventId, eventHandler);
		}
	}
	inline void				AttachEvent(EventID eventId, EventHandler& eventHandler)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->AttachEvent(eventId, eventHandler);
		}
	}
	inline void				SendEvent(ExecutorID execId, EventID eventId, void* pData)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SendEvent(execId, eventId, pData);
		}
	}
	inline void				SendEvent(EventID eventId, void* pData)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SendEvent(eventId, pData);
		}
	}
	inline void				SendEventToHandler(ExecutorID execId, EventID eventId, EventHandler& eventHandler, void* pData)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SendEventToHandler(execId, eventId, eventHandler, pData);
		}
	}
	inline void				SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SendEventToHandler(eventId, eventHandler, pData);
		}
	}
	inline void				AttachComponentEvent(ExecutorID execId, EventID eventId, GameObject* obj, EventHandler& eventHandler)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->AttachComponentEvent(execId, eventId, obj->GetId(), eventHandler);
		}
	}
	inline void				AttachComponentEvent(EventID eventId, GameObject* obj, EventHandler& eventHandler)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->AttachComponentEvent(eventId, obj->GetId(), eventHandler);
		}
	}
	inline void				SendComponentEvent(ExecutorID execId, EventID eventId, GameObject* obj, void* pData)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SendComponentEvent(execId, eventId, obj->GetId(), pData);
		}
	}
	inline void				SendComponentEvent(EventID eventId, GameObject* obj, void* pData)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SendComponentEvent(eventId, obj->GetId(), pData);
		}
	}
	inline void				SendComponentEventToHandler(ExecutorID execId, EventID eventId, GameObject* obj, EventHandler& eventHandler, void* pData)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SendComponentEventToHandler(execId, eventId, obj->GetId(), eventHandler, pData);
		}
	}
	inline void				SendComponentEventToHandler(EventID eventId, GameObject* obj, EventHandler& eventHandler, void* pData)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if (pEventManager)
		{
			pEventManager->SendComponentEventToHandler(eventId, obj->GetId(), eventHandler, pData);
		}
	}
	inline void				BroadcastComponentEvent(EventID eventId, std::vector<GameObject*>* objects, void* pData)
	{
		std::vector<GameObject*>::iterator it;
		for (it = objects->begin(); it != objects->end(); it++)
		{
			SendComponentEvent(eventId, (*it), pData);
		}
	}
}

#endif//__EVENTMANAGER_H__
