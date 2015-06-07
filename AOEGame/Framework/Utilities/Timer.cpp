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
			, m_timeTotal(0.0f)
	{
		
		

		int game_width = GameConfig::GetSingletonPtr()->GetInt(std::string(ConfigKey::GAME_WIDTH));
		float game_width2 = GameConfig::GetSingletonPtr()->GetInt("TestFloat1");
		float game_width3 = GameConfig::GetSingletonPtr()->GetFloat("TestFloat2");
		float game_width4 = GameConfig::GetSingletonPtr()->GetFloat("TestFloat22");
		float game_width5 = GameConfig::GetSingletonPtr()->GetFloat("TestFloat25");
		bool gameFullScreen = GameConfig::GetSingletonPtr()->GetBool("FULLSCREEN");
		//test
		m_timeTotal = 0;
		Log::info(Log::LOG_LEVEL_ROOT, "[Timer] Constructor Get Config %d, %f, %f, %f !\n", game_width, game_width2, game_width3, game_width4);
	}

	Timer::~Timer()
	{
	}

	Timer::TimeUints Timer::nanoTime()
	{
		TimeUints timeNow;
		QueryPerformanceCounter(&timeNow);
		return timeNow;
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
		//QueryPerformanceFrequency(&m_timeFreq);

		QueryPerformanceCounter(&m_timeStart);

		m_anim = ((float)m_timeStart.QuadPart - (float)m_timeLastFrame.QuadPart) / m_timeFreq.QuadPart;
		

		LONGLONG llTimeDiff = m_timeStart.QuadPart - m_timeLastFrame.QuadPart;

		m_frameDt = (m_timeStart.QuadPart - m_timeLastFrame.QuadPart) / (double)(m_timeFreq.QuadPart / 1000.0f);//mili seconds

		//double m_dt = (m_timeStart.QuadPart - m_timeLastFrame.QuadPart) / (double)(m_timeFreq.QuadPart / 1000.0f);

		//Log::info(Log::LOG_LEVEL_ROOT, "[Timer][Update] TimeDt %f !\n", m_dt);
		m_simDt = m_frameDt * m_simMultiplier;

		m_timeTotal += m_frameDt; //
		//Log::info(Log::LOG_LEVEL_ROOT, "[Timer][Update] TimeTotal %f !\n", Timer::GetTimeTotal());
		m_timeLastFrame = m_timeStart;

		
		int k = 124;
	}

	void Timer::OnResume()
	{
		m_timeLastFrame = nanoTime();
	}

	void Timer::Stop()
	{
	}
}