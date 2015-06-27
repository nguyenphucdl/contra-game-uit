#ifndef __HEALTH_FUNCTION_H__
#define __HEALTH_FUNCTION_H__

#include "../Component.h"
#include "../../Math/Vector3.h"
#include "../../Utilities/Timer.h"


namespace Framework
{
	class HealthFunction
	{
	private:
		int		 m_origin;
		int		 m_health;
		bool	 m_isDead;
		float	 m_eslapse;
		float	 m_delay;

	public:
		HealthFunction() : m_eslapse(5.0f), m_delay(0.15f) {};
		virtual ~HealthFunction() {};
		void SetHealth(int health)		{ m_health = health; m_origin = m_health; }
		float GetPercentage()			{ return (float)m_health / (float)m_origin; }

		void Damage(int damange);
		void UpdateHealthFunc();
	protected:
		
		void Recover()					{ m_health = m_origin; }
		bool IsRunOutOfHealth()			{ return m_health <= 0; }
	};
	inline void HealthFunction::Damage(int damange)
	{ 
		if (m_eslapse > m_delay)
		{
			m_health -= damange;
			m_eslapse = 0.0f;
		}
	}

	inline void HealthFunction::UpdateHealthFunc()
	{
		m_eslapse += Timer::GetSingletonPtr()->GetTimeSim();
	}
}
#endif//__HEALTH_FUNCTION_H__