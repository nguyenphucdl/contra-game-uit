#ifndef __TIMING_FUNCTION_H__
#define __TIMING_FUNCTION_H__

#include "../Component.h"
#include "../../EventManager/EventManager.h"
#include "../../Math/Vector3.h"
#include "../../Utilities/Timer.h"


namespace Framework
{
	class TimingFunction
	{
	protected:
		float		m_eslapse;
		float		m_delay;
		float		m_actionEslapse;
		float		m_actionDelay;
		float		m_updateDelay;
		float		m_updateEslapse;

		bool		m_action;
		bool		m_update;
		bool		m_start;

		std::default_random_engine m_generator;
		std::uniform_int_distribution<int> m_distribution;
	public:
		TimingFunction();
		virtual ~TimingFunction() {};
	protected:
		bool IsAction();
		void ResetTiming();
		bool Wait(float time);
		bool Wait(float time, float action);
		bool IsUpdate() { return m_update; }
		void UpdateTimingFunc();
		int RandomInRange();
		int RandomInRange(int min, int max);


	};
	inline int TimingFunction::RandomInRange()
	{
		return m_distribution(m_generator);
	}

	inline int TimingFunction::RandomInRange(int min, int max)
	{
		return 3;
	}

	inline bool TimingFunction::Wait(float time, float action)
	{
		m_delay = time;
		m_actionDelay = action;
		return m_action;
	}

	inline bool TimingFunction::Wait(float time)
	{
		m_delay = time;
		return m_action;
	}

	inline bool TimingFunction::IsAction()
	{
		return m_action;
	}

	inline void TimingFunction::ResetTiming()
	{
		m_eslapse = 0.0f;
	}
}
#endif//__TIMING_COMPONENT_H__