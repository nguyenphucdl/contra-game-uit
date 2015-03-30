#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include "../Application/Context.h"
#include <unordered_map>
#include "../Kernel/Task.h"
#include "EventId.h"
#include "Event.h"

namespace Framework
{
	class EventManager
		: public Singleton<EventManager>
	{
		friend void SendEvent(EventID eventId, void* pData);
		friend void SendEventToHandler(EventID eventId, EventHandler& eventHandler, void *pData);
		friend bool RegisterEvent(EventID eventId);
		friend void AttachEvent(EventID eventId, EventHandler& eventHandler);
		friend void DetachEvent(EventID eventId, EventHandler& eventHandler);

		friend class Log;

	private:
		typedef std::tr1::unordered_map<EventID, Event*>	EventMap;
		typedef EventMap::iterator							EventMapIterator;

		EventMap								m_eventMap;

		void SendEvent(EventID eventId, void* pData);
		void SendEventToHandler(EventID eventId, EventHandler& eventHandler, void* pData);
		bool RegisterEvent(EventID eventId);
		void AttachEvent(EventID eventId, EventHandler& eventHandler);
		void DetachEvent(EventID eventId, EventHandler& eventHandler);

	public:
		EventManager();
		~EventManager();
	};

	inline void SendEvent(EventID eventId, void* pData = NULL)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if(pEventManager)
		{
			pEventManager->SendEvent(eventId, pData);
		}
	}

	inline void SendEventToHandler(EventID eventId, EventHandler& eventHandler, void *pData = NULL)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if(pEventManager)
		{
			pEventManager->SendEventToHandler(eventId, eventHandler, pData);
		}
	}

	inline bool RegisterEvent(EventID eventId)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if(pEventManager)
		{
			return pEventManager->RegisterEvent(eventId);
		}
		return false;
	}

	inline void AttachEvent(EventID eventId, EventHandler& eventHandler)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if(pEventManager)
		{
			pEventManager->AttachEvent(eventId, eventHandler);
		}
	}

	inline void DetachEvent(EventID eventId, EventHandler& eventHandler)
	{
		EventManager* pEventManager = EventManager::GetSingletonPtr();
		assert(pEventManager);
		if(pEventManager)
		{
			pEventManager->DetachEvent(eventId, eventHandler);
		}
	}
}

#endif//__EVENTMANAGER_H__
