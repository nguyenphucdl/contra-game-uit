#include "Event.h"
#include <cassert>

namespace Framework
{
	Event::Event(EventID eventId)
		:	m_id(eventId)
		,	m_pData(NULL)
		, m_listeners()
	{
	}

	Event::~Event()
	{
		/*for (EventHandlerListIterator it = m_listeners.begin(); it != m_listeners.end(); it++)
		{
			EventHandler* handler = *it;
			if (handler != NULL)
			{
				delete handler;
				handler = NULL;
			}
			
			*it = NULL;
		}*/
		m_listeners.clear();
		m_listeners.shrink_to_fit();
	}

	void Event::Send(void* pData)
	{
		m_pData = pData;
		for(EventHandlerListIterator iter = m_listeners.begin(); iter != m_listeners.end(); ++iter)
		{
			EventHandler* pEventHandler = *iter;
			assert(pEventHandler);
			if(pEventHandler)
			{
				pEventHandler->HandleEvent(this);
			}
		}
	}

	void Event::SendToHandler(EventHandler& eventHandler, void* pData)
	{
		m_pData = pData;
		for(EventHandlerListIterator iter = m_listeners.begin(); iter != m_listeners.end(); ++iter)
		{
			if(&eventHandler == *iter)
			{
				eventHandler.HandleEvent(this);
			}
		}
	}

	void Event::AttachListener(EventHandler& eventHandler)
	{
		for (EventHandlerListIterator iter = m_listeners.begin(); iter != m_listeners.end(); ++iter)
		{
			if (&eventHandler == *iter)
			{
				return;
			}
		}
		m_listeners.push_back(&eventHandler);
	}

	void Event::DetachListener(EventHandler& eventHandler)
	{
		for(EventHandlerListIterator iter = m_listeners.begin(); iter != m_listeners.end(); ++iter)
		{
			if(&eventHandler == *iter)
			{
				m_listeners.erase(iter);
				break;
			}
		}
	}
}