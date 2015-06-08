#ifndef __EVENTEXECUTOR_AWARE_ID_H__
#define __EVENTEXECUTOR_AWARE_ID_H__

#include "../Utilities/Utils.h"

namespace Framework
{
	typedef unsigned int ExecutorID;
	class EventExecutorAware
	{
	public:
		explicit EventExecutorAware()
			: m_executorId(Utils::getNextExecId())
		{

		}
		virtual ~EventExecutorAware() { };

		ExecutorID  GetExecutorId() { return m_executorId; }
	private:
		void		SetExecutorId(ExecutorID id) { m_executorId = id; }
	
		ExecutorID	m_executorId;

		friend class EventManager;
	};
}
#endif