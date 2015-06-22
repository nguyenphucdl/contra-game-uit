#include "GameStateManager.h"
#include "../EventManager/EventManager.h"
#include "../Utilities/Timer.h"
#include "../Utilities/Console.h"
#include "../Utilities/FPSCounter.h"

namespace Framework
{
	GameStateManager::GameStateManager(const unsigned int priority)
		: Task(priority, "GamePlay1Task")
		, m_paused(false)
		, m_eslapsed(0.0f)
	{
	}

	GameStateManager::~GameStateManager()
	{
	}

	void GameStateManager::Switch(GameState* state)
	{

	}

	GameState* GameStateManager::Pop()
	{
		return nullptr;
	}

	void GameStateManager::Push(GameState* state)
	{

	}

	GameState* GameStateManager::Peek()
	{
		return nullptr;
	}

	bool GameStateManager::Start()
	{
		//Framework::AttachEvent(ExecutorIDs::SysInput, Events::SYS_PAUSE_RESUME_EVENT, *this);
		Framework::AttachEvent(ExecutorIDs::SysInput, Events::SYS_PAUSE_EVENT, *this);
		Framework::AttachEvent(ExecutorIDs::SysInput, Events::SYS_RESUME_EVENT, *this);

		m_currentGamePlay = new GamePlay();
		m_currentGamePlay->Init();
		return true;
	}

	void GameStateManager::OnSuspend()
	{

	}

	void GameStateManager::Update()
	{
		if (!m_paused)
		{
			m_currentGamePlay->Update();
		}
		if (Timer::GetSingletonPtr()->StopWatch(TimerTypes::RenderCount, 0.0166666667f))
		{
			m_currentGamePlay->Draw();
		}
	}

	void GameStateManager::OnResume()
	{

	}

	void GameStateManager::Stop()
	{

	}

	void GameStateManager::HandleEvent(Event* pEvent)
	{
		switch (pEvent->GetID())
		{
		case Events::SYS_PAUSE_EVENT:
			m_paused = (bool)pEvent->GetData();
			break;
		case Events::SYS_RESUME_EVENT:
			m_paused = false;
			break;
		default:
			break;
		}
	}
}