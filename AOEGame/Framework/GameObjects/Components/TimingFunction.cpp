#include"TimingFunction.h"
#include "../../Utilities/Console.h"

namespace Framework
{
	TimingFunction::TimingFunction()
		: m_eslapse(0.0f)
		, m_delay(5.0f)
		, m_actionEslapse(0.0f)
		, m_actionDelay(2.0f)
		, m_action(false)
		, m_start(true)
		, m_distribution(0, 6)
		, m_updateEslapse(0.0f)
		, m_updateDelay(0.5f)
		, m_update(true)
	{
		
	}

	void TimingFunction::UpdateTimingFunc()
	{

		if (m_start)
		{
			m_eslapse += Timer::GetSingletonPtr()->GetTimeSim();

			if (!m_action && m_eslapse > m_delay)
			{
				m_action = true;
				m_actionEslapse = 0.0f;
			}

			/*if (m_update && m_eslapse > m_delay)
			{
				m_update = true;
				m_updateEslapse = 0.0f;
			}*/

			if (m_action)
			{
				m_actionEslapse += Timer::GetSingletonPtr()->GetTimeSim();
				if (m_actionEslapse > m_actionDelay)
				{
					m_action = false;
					//m_eslapse = 0.0f;
				}
			}

			
			/*m_updateEslapse += Timer::GetSingletonPtr()->GetTimeSim();
			if (m_actionEslapse > m_updateDelay)
			{
				m_update = true;
				m_updateEslapse = 0.0f;	
			}
			else
			{
				m_update = false;
			}*/
			
		}
	}
}