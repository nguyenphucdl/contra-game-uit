#ifndef __TASK_H__
#define __TASK_H__

#include "../Application/Context.h"

namespace Framework
{
	class Task
	{
	private:
		unsigned int	m_priority;
		bool			m_canKill;
		std::string		m_name;
	public:
		explicit Task(const unsigned int priority);
		explicit Task(const unsigned int priority, const char* name);
		virtual ~Task();

		virtual bool	Start()		= 0;
		virtual void	OnSuspend()	= 0;
		virtual void	Update()	= 0;
		virtual void	OnResume()	= 0;
		virtual void	Stop()		= 0;

		void			SetCanKill(const bool canKill);
		bool			CanKill() const;
		unsigned int	Priority() const;
		std::string		GetName() const;

		static const unsigned int	TIMER_PRIORITY		= 0;
		static const unsigned int	PLATFORM_PRIORITY	= 1000;
		static const unsigned int	FILE_PRIORITY		= 2000;
		static const unsigned int	GAME_PRIORITY		= 3000;
		static const unsigned int	AUDIO_PRIORITY		= 4000;
		static const unsigned int	RENDER_PRIORITY		= 5000;		
	};

	inline Task::Task(const unsigned int priority)
		: m_priority(priority)
		, m_canKill(false)
		, m_name("Unnamed Task")
	{
		
	}

	inline Task::Task(const unsigned int priority, const char* name)
		: m_priority(priority)
		, m_canKill(false)
		, m_name(name)
	{
		
	}

	inline Task::~Task()
	{
	}

	inline void Task::SetCanKill(const bool canKill)
	{
		m_canKill = canKill;
	}

	inline bool Task::CanKill() const
	{
		return	m_canKill;
	}

	inline unsigned int Task::Priority() const
	{
		return m_priority;
	}
	inline std::string Task::GetName() const 
	{
		return m_name;
	}
}

#endif //__TASK_H__