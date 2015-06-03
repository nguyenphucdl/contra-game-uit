#ifndef __EVENTEXECUTOR_AWARE_ID_H__
#define __EVENTEXECUTOR_AWARE_ID_H__

namespace Framework
{
	typedef unsigned int ExecutorID;
	class EventExecutorAware
	{
	public:
		explicit EventExecutorAware(ExecutorID id)
			: m_executorId(id)
		{

		}
		virtual ~EventExecutorAware() { };

		ExecutorID  GetExecutorId() { return m_executorId; }
	private:
		ExecutorID	m_executorId;
	};
}
#endif