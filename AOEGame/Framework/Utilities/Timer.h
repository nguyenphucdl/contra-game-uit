#ifndef __TIMER_H__
#define __TIMER_H__

#include "../Kernel/Task.h"

namespace Framework
{
	class Timer
		:	public Task
		,	public Singleton<Timer>
	{
	public:
		typedef LARGE_INTEGER					TimeUints;
		typedef std::vector<double>				TimerEslapsedVector;
		typedef TimerEslapsedVector::iterator	TimerEslapsedVectorIterator;

	private:
		std::vector<double>		m_timesEslapsed;

		TimeUints		m_timeStart;
		TimeUints		m_timeLastFrame;
		TimeUints		m_timeFreq;

		double			m_frameDt;
		double			m_simDt;
		double			m_simMultiplier;

	public:
		Timer(const unsigned int priority);
		~Timer();

		double			GetTimeEslapsed(int timerType) const;
		double			GetTimeFrame() const;
		double			GetTimeSim() const;
		void			Reset(int timerType);
		void			ResetAll();
		void			SetSimMultiplier(const double simMultiplier);
		void			AddTimer(int timerType);
		bool			StopWatch(int timerType, double eslapsed);

		virtual bool	Start();
		virtual void	OnSuspend();
		virtual void	Update();
		virtual void	OnResume();
		virtual void	Stop();
	};

	inline double Timer::GetTimeFrame() const
	{
		return m_frameDt;
	}

	inline double Timer::GetTimeEslapsed(int timerType) const
	{
		return m_timesEslapsed[timerType];
	}

	inline void	Timer::AddTimer(int timerType)
	{
		try {
			double temp = m_timesEslapsed.at(timerType);
		}
		catch (const std::out_of_range& oor) {
			Log::error("Try to register event with id out of range (%d) reson (%s)", timerType, oor.what());
			throw new GameError(GameErrorNS::FATAL_ERROR, oor.what());
		}
	}

	inline bool	Timer::StopWatch(int timerType, double eslapsed)
	{
		if (m_timesEslapsed[timerType] >= eslapsed)
		{
			m_timesEslapsed[timerType] = 0.0f;
			return true;
		}
		return false;
	}

	inline double Timer::GetTimeSim() const
	{
		return m_simDt;
	}
	
	inline void Timer::ResetAll()
	{
		std::fill(m_timesEslapsed.begin(), m_timesEslapsed.end(), 0.0f);
	}

	inline void Timer::Reset(int timerType)
	{
		m_timesEslapsed[timerType] = 0.0f;
	}

	inline void Timer::SetSimMultiplier(const double simMultiplier)
	{
		m_simMultiplier = simMultiplier;
	}
}
#endif //__TIMER_H__