#include "Timer.h"
#include "Console.h"

namespace Framework
{
	Timer::Timer(const unsigned int priority)
			: Task(priority, "Timer Task")
			, m_timeLastFrame()
			, m_timeFreq()
			, m_frameDt(0.0f)
			, m_simDt(0.0f)
			, m_simMultiplier(1.0f)
			, m_timesEslapsed(5)
	{
		std::fill(m_timesEslapsed.begin(), m_timesEslapsed.end(), 0.0f);
	}

	Timer::~Timer()
	{
	}

	bool Timer::Start()
	{
		if(QueryPerformanceFrequency(&m_timeFreq) == false)
			throw(GameError(GameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));
		Log::info(Log::LOG_LEVEL_ROOT, "[Timer][Start] Successfully !\n");
		QueryPerformanceCounter(&m_timeLastFrame);
		return true;
	}

	void Timer::OnSuspend()
	{
		
	}

	void Timer::Update()
	{
		QueryPerformanceCounter(&m_timeStart);

		m_frameDt = ((double)(m_timeStart.QuadPart - m_timeLastFrame.QuadPart)) / m_timeFreq.QuadPart;
		
		m_simDt = m_frameDt * m_simMultiplier;		

		for (TimerEslapsedVectorIterator it = m_timesEslapsed.begin(); it != m_timesEslapsed.end(); it++)
		{
			*it += m_simDt;
		}
		
		m_timeLastFrame = m_timeStart;
	}

	void Timer::OnResume()
	{
		
	}

	void Timer::Stop()
	{
	}
}