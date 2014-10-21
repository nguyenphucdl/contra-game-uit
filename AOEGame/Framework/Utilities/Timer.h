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
		typedef LARGE_INTEGER	TimeUints;

	private:
		TimeUints		nanoTime();
		TimeUints		m_timeStart;
		TimeUints		m_timeLastFrame;
		TimeUints		m_timeFreq;
		float			m_timeTotal; //Test
		
		float			m_frameDt;
		float			m_simDt;
		float			m_simMultiplier;

	public:
		Timer(const unsigned int priority);
		~Timer();

		float			GetTimeFrame() const;
		float			GetTimeSim() const;
		float			GetTimeTotal() const;
		void			Reset();
		void			SetSimMultiplier(const float simMultiplier);

		virtual bool	Start();
		virtual void	OnSuspend();
		virtual void	Update();
		virtual void	OnResume();
		virtual void	Stop();
	};

	inline float Timer::GetTimeFrame() const
	{
		return m_frameDt;
	}

	inline float Timer::GetTimeSim() const
	{
		return m_simDt;
	}
	inline float Timer::GetTimeTotal() const
	{
		return m_timeTotal;
	}
	inline void Timer::Reset()
	{
		m_timeTotal = 0;
	}
	inline void Timer::SetSimMultiplier(const float simMultiplier)
	{
		m_simMultiplier = simMultiplier;
	}
}
#endif //__TIMER_H__